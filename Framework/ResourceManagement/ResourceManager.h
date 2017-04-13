#pragma once

#include <string>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <future>
#include <assert.h>

namespace IO
{
    class InputStream;
}

namespace ResourceManagement
{
    class Resource;
    class ResourceLoader;

    ///
    /// Mogren resource manager
    ///
    class ResourceManager final
    {
    public:
        ///
        /// Initializes a new instance of the resource manager.
        ///
        ResourceManager();

        ///
        /// Adds new resource loader to resource manager.
        /// If the loader is able to load the same resources as one
        /// or more of the previous loaders, previous loaders are replaced
        /// with given loader.
        ///
        void addResourceLoader(std::unique_ptr<ResourceLoader> resourceLoader);

        ///
        /// Gets the resource stream.
        /// Throws WrongResourceException if resource doesn't exist.
        ///
        /// \param path The resource path.
        /// \returns InputStream instance.
        std::unique_ptr<IO::InputStream> openResourceStream(const std::string &path) const;

        ///
        /// Loads all resources located in the given directory and all its subdirectories.
        /// \param path The directory path.
        /// \param callback The callback called after the loading is finished. The callback is dispatched to main thread.
        ///
        void loadResources(const std::string& filter, std::function<void()> callback);

        ///
        /// Removes references to all resources loaded from given directory.
        ///
        void unloadResources(const std::string& filter);

        ///
        /// Return the previously loaded resource.
        /// Throws WrongResourceException if the resource was not loaded.
        /// \path The resource path.
        ///
        template <typename TRes>
        typename std::shared_ptr<TRes> getResource(const std::string &path) const;

        ///
        /// Must be called from main thread to finalize loaded resources
        ///
        void finalizeResources();

        ~ResourceManager();

    private:
        ///
        /// Returns the extension of the given file.
        ///
        static std::string getFileExtension(const std::string& path);

        ///
        /// Loads resource from the given path and stores it to the mLoadedResources map.
        /// Throws WrongResourceException if resource doesn't exist or has a wrong type.
        /// \param path The path to the resource to be loaded.
        ///
        std::shared_ptr<Resource> loadResource(const std::string &path);

        ///
        /// Loads resource from the given path and stores it to the mLoadedResources map.
        /// Throws WrongResourceException if resource doesn't exist or has a wrong type.
        /// \param path The path to the resource to be loaded.
        /// \param resourceLoader Resource loader used to load the resource.
        ///
        std::shared_ptr<Resource> loadResource(const std::string &path, ResourceLoader& resourceLoader);

        ///
        /// Gets the full resource path (with locale) from short path (without locale).
        /// Throws WrongResourceException If resource not found
        ///
        /// \param path The short resource path.
        ///
        std::string getFullResourcePath(const std::string &path) const;

        ///
        /// Gets the locales and resource path from full resource path.
        ///
        /// \param fullResPath The full resource path.
        /// \param locales The locales list.
        /// \param resPath The resource path.
        void getLocalesAndResourcePathFromFullResourcePath(
            const std::string &fullResPath, std::vector<std::string> &locales, std::string &resPath);

        ///
        /// Calculates the culture equality value.
        ///
        /// \param culture1Name Name of the first culture.
        /// \param culture2Name Name of the second culture.
        ///
        static int calculateCultureEqualityValue(const std::string &culture1Name, const std::string &culture2Name);

        public:
            ///
            /// The default culture resources folder name.
            ///
            static const std::string DefaultCultureFolderName;

    private:
        ///
        /// Resource loaders map (file extension -> loader ptr)
        ///
        std::unordered_map< std::string, std::shared_ptr<ResourceLoader> > mResourceLoaders;

        ///
        /// Dictionary of the localized resources paths.
        ///
        std::unordered_map<std::string, std::string> mLocalizedResourcesPaths;

        ///
        /// The mutex for all resource list operations
        ///
        mutable std::mutex mLoadedResourcesMutex;

        ///
        /// The loaded resources list
        ///
        std::unordered_map<std::string, std::shared_ptr<Resource>> mLoadedResources;

        struct ResourcesLoadingFutureData
        {
            using tLoadedResourcesList = std::vector<std::shared_ptr<Resource>>;
            std::future<tLoadedResourcesList> future;
            std::function<void()> callback;
        };

        std::vector<ResourcesLoadingFutureData> mResourcesLoadingFutures;

        volatile bool mCancelResourcesLoading;
    };

    template<typename TRes>
    inline typename std::shared_ptr<TRes> ResourceManager::getResource(const std::string & path) const
    {
        std::lock_guard<std::mutex> lock(mLoadedResourcesMutex);

        auto loadedResIter = mLoadedResources.find(path);

        if (loadedResIter != mLoadedResources.end() && loadedResIter->second != nullptr)
        {
            auto res = std::dynamic_pointer_cast<TRes>(loadedResIter->second);
            assert(res != nullptr);
            return res;
        }

        return nullptr;
    }
}

