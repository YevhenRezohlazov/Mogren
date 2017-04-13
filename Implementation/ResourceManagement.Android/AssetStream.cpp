#include "AssetStream.h"

#include <Mogren/Implementation/Core.Android/AndroidCoreImpl.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>

namespace ResourceManagement
{
	AssetStream::AssetStream(const std::string& assetPath)
	{
		mPosition = 0;

		mAsset = AAssetManager_open(
			static_cast<Common::AndroidCoreImpl&>(Common::getImpl<Common::NativeCoreInterface>()).getAssetManager(),
			assetPath.c_str(),
			AASSET_MODE_UNKNOWN);
	}

	void AssetStream::setPosition(uint32_t position)
	{
		auto newPos = AAsset_seek(mAsset, position, SEEK_SET);

		if (newPos != -1)
		{
			mPosition = newPos;
		}
	}

    uint32_t AssetStream::getPosition() const
	{
		return mPosition;
	}

    uint32_t AssetStream::getLength() const
	{
		return AAsset_getLength(mAsset);
	}

	bool AssetStream::canRead() const
	{
		return mPosition < getLength();
	}

    uint32_t AssetStream::read(void* buffer, uint32_t size)
	{
		auto bytesRead = AAsset_read(mAsset, buffer, size);
		mPosition += bytesRead;
		return bytesRead;
	}

	AssetStream::~AssetStream()
	{
		AAsset_close(mAsset);
	}
}
