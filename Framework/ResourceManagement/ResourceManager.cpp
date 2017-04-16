#include "ResourceManager.h"
#include "Resource.h"
#include "ResourceLoader.h"
#include "NativeInterface/NativeResourceManager.h"

#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Common/NativeInterface/NativeCoreInterface.h>
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>
#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/BinaryReader.h>

#include <assert.h>
#include <array>
#include <algorithm>
#include <chrono>

namespace ResourceManagement
{
    const std::string ResourceManager::DefaultCultureFolderName = "Default";

    ResourceManager::ResourceManager()
        : mCancelResourcesLoading(false)
    {
        std::vector<std::string> resFiles;

        {
            auto resListStream = Common::getImpl<NativeResourceManager>().openStream("ResList.bin");
            assert(resListStream);
            IO::BinaryReader resListReader(*resListStream);

            auto resCount = resListReader.read<int32_t>();
            resFiles.reserve(resCount);

            for (int i = 0; i < resCount; ++i)
            {
                auto stringLen = resListReader.read<int32_t>();
                auto resPath = resListReader.readString(stringLen);
                resFiles.push_back(resPath);
            }
        }

        struct LocaleGroup
        {
            std::string locale;
            std::string path;
            std::string fullPath;

            LocaleGroup(std::string locale, std::string path, std::string fullPath)
                : locale(locale), path(path), fullPath(fullPath)
            {
            }
        };

        std::unordered_map<std::string, std::vector<LocaleGroup>> localeGroups;
        std::vector<std::string> fileLocales;

        for (auto & resFile : resFiles)
        {
            std::string path;
            fileLocales.clear();
            getLocalesAndResourcePathFromFullResourcePath(resFile, fileLocales, path);

            for (auto &locale : fileLocales)
            {
                localeGroups[locale].push_back(LocaleGroup(locale, path, resFile));
            }
        }

        auto defaultGroup = localeGroups[DefaultCultureFolderName];

        if (defaultGroup.empty())
        {
            Logging::Logger::writeError("No default locale resources folder found. No resources will be available.");
            return;
        }

        if (localeGroups.find("") != localeGroups.end())
        {
            Logging::Logger::writeError("There are resources in root resources folder. Resources should be grouped by locale folders. Example: en-US/MyAwsomeImage.png");
        }

        // fill elements from default locale
        for (auto resElem : defaultGroup)
        {
            mLocalizedResourcesPaths[resElem.path] = resElem.fullPath;
        }

        auto currentLocaleName = Common::getImpl<Common::NativeCoreInterface>().getLocaleName();
        Logging::Logger::writeInfo("Locale: %s", currentLocaleName.c_str());

        auto bestLocale = DefaultCultureFolderName;
        auto bestLocaleEqualityValue = 0;

        for (auto & group : localeGroups)
        {
            if (group.first == DefaultCultureFolderName) continue;

            const auto eqValue = calculateCultureEqualityValue(group.first, currentLocaleName);

            if (eqValue > bestLocaleEqualityValue)
            {
                bestLocaleEqualityValue = eqValue;
                bestLocale = group.first;
            }
        }

        if (bestLocale == DefaultCultureFolderName)
        {
            Logging::Logger::writeInfo("No specific locale resources found. Using default locale resources.");
        }
        else
        {
            Logging::Logger::writeInfo("Locale-specific resources are loading from %s folder.", bestLocale.c_str());

            auto bestLocaleElems = localeGroups[bestLocale];

            // fill locale-specific elements
            for (auto resElem : bestLocaleElems)
            {
                if (mLocalizedResourcesPaths.find(resElem.path) == mLocalizedResourcesPaths.end())
                {
                    Logging::Logger::writeWarning("%s found in %s locale, but not available in default locale.",
                        resElem.path.c_str(), resElem.locale.c_str());
                }

                mLocalizedResourcesPaths[resElem.path] = resElem.fullPath;
            }
        }
    }

    void ResourceManager::finalizeResources()
    {
        for (int i = mResourcesLoadingFutures.size() - 1; i >= 0; --i)
        {
            using namespace std::chrono_literals;
            auto & futData = mResourcesLoadingFutures[i];
            if (futData.future.wait_for(0s) == std::future_status::ready)
            {
                auto loadedResources = futData.future.get();
                for (auto & loadedRes : loadedResources)
                {
                    if (loadedRes != nullptr)
                        loadedRes->finalize();
                }

                futData.callback();
                mResourcesLoadingFutures.erase(mResourcesLoadingFutures.cbegin() + i);
            }
        }
    }

    ResourceManager::~ResourceManager()
    {
    }

    void ResourceManager::addResourceLoader(std::unique_ptr<ResourceLoader> resourceLoader)
    {
        std::shared_ptr<ResourceLoader> sharedResLoader = std::move(resourceLoader);
        for (auto &ext : sharedResLoader->getResourceExtensions())
        {
            mResourceLoaders[ext] = sharedResLoader;
        }
    }

    std::unique_ptr<IO::InputStream> ResourceManager::openResourceStream(const std::string &path) const
    {
        auto resPath = getFullResourcePath(path);
        Logging::Logger::writeInfo("Opening stream from %s", resPath.c_str());
        return Common::getImpl<NativeResourceManager>().openStream(resPath);
    }

    std::shared_ptr<Resource> ResourceManager::loadResource(const std::string &path)
    {
        auto loaderIter = mResourceLoaders.find(getFileExtension(path));

        if (loaderIter == mResourceLoaders.end())
        {
            Logging::Logger::writeInfo("Can't find loader to load %s. File must be loaded manually.", path.c_str());
            return nullptr;
        }

        return loadResource(path, *loaderIter->second);
    }

    std::shared_ptr<Resource> ResourceManager::loadResource(const std::string &path, ResourceLoader &resourceLoader)
    {
        Logging::Logger::writeInfo("Loading resource from %s", path.c_str());
        auto resultResource = resourceLoader.loadResource(*openResourceStream(path));
        std::lock_guard<std::mutex> lock(mLoadedResourcesMutex);
        return mLoadedResources[path] = std::move(resultResource);
    }

    std::string ResourceManager::getFullResourcePath(const std::string &path) const
    {
        auto res = mLocalizedResourcesPaths.find(path);

        if (res == mLocalizedResourcesPaths.end())
        {
            Logging::Logger::writeError("%s resource hasn't been found.", path.c_str());
            return std::string();
        }

        return res->second;
    }

    void ResourceManager::getLocalesAndResourcePathFromFullResourcePath(
        const std::string &fullResPath, std::vector<std::string> &locales, std::string &resPath)
    {
        auto slashPos = fullResPath.find('/');

        if (slashPos != std::string::npos)
        {
            std::string::size_type prevPos = 0;
            
            while (true)
            {
                auto commaPos = fullResPath.find(',', prevPos);
                if (commaPos == std::string::npos || commaPos > slashPos)
                    break;
                locales.push_back(fullResPath.substr(prevPos, commaPos - prevPos));
                prevPos = commaPos + 1;
            }

            locales.push_back(fullResPath.substr(prevPos, slashPos - prevPos));

            resPath = fullResPath.substr(slashPos + 1);
        }
        else
        {
            resPath = std::string();
        }
    }

    int ResourceManager::calculateCultureEqualityValue(const std::string &culture1Name, const std::string &culture2Name)
    {
        int res = 0;

        for (uint32_t i = 0; i < Math::minimum(culture1Name.size(), culture2Name.size()); ++i)
        {
            if (culture1Name[i] == culture2Name[i])
            {
                res += 1;
            }
            else
            {
                break;
            }
        }

        return res;
    }

    std::string ResourceManager::getFileExtension(const std::string& path)
    {
        auto dotPos = path.rfind('.');

        if (dotPos == std::string::npos)
        {
            return std::string();
        }

        return path.substr(dotPos + 1);
    }

    void ResourceManager::loadResources(const std::string &path, std::function<void()> callback)
    {
        std::vector<std::string> resourcesToLoad;

        {
            std::unique_lock<std::mutex> lock(mLoadedResourcesMutex);

            for (auto iter = mLocalizedResourcesPaths.begin(); iter != mLocalizedResourcesPaths.end(); ++iter)
            {
                if (iter->first.compare(0, path.length(), path) == 0 && mLoadedResources.find(iter->first) == mLoadedResources.end())
                {
                    mLoadedResources[iter->first] = nullptr;
                    resourcesToLoad.push_back(iter->first);
                }
            }
        }

        if (resourcesToLoad.empty())
        {
            callback();
        }
        else
        {
            auto resLoadingFuture = std::async(
                std::launch::async,
                [this, resourcesToLoad]()
                {
                    DECLARE_FUNCTION_LOGGING_GUARD();

                    ResourcesLoadingFutureData::tLoadedResourcesList loadedResList;
                    loadedResList.reserve(resourcesToLoad.size());

                    for (auto i = resourcesToLoad.begin(); i != resourcesToLoad.end(); ++i)
                    {
                        if (mCancelResourcesLoading) break;
                        loadedResList.push_back(loadResource(*i));
                    }

                    return loadedResList;
                });

            mResourcesLoadingFutures.push_back({ std::move(resLoadingFuture), std::move(callback) });
        }
    }

    void ResourceManager::unloadResources(const std::string& path)
    {
        std::lock_guard<std::mutex> lock(mLoadedResourcesMutex);

        for (auto iter = mLoadedResources.begin(); iter != mLoadedResources.end();)
        {
            if (iter->first.compare(0, path.length(), path) == 0)
            {
                Logging::Logger::writeInfo("Resource unloaded: %s", iter->first.c_str());
                iter = mLoadedResources.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}