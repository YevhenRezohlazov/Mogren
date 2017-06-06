#include "TextureLoader.h"
#include "Texture.h"
#include "NativeInterface/NativeGraphicsInterface.h"
#include "NativeInterface/NativeTexture.h"
#include "Utils.h"

#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>
#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/BinaryReader.h>
#include <Mogren/Framework/Common/ImplementationProvider.h>

#include <assert.h>

namespace Graphics
{
    TextureLoader::TextureLoader()
    {
    }

    const std::vector<std::string> TextureLoader::getResourceExtensions() const
    {
        return { "png" };
    }

    std::unique_ptr<ResourceManagement::Resource> TextureLoader::loadResource(IO::InputStream & stream) const
    {
        DECLARE_FUNCTION_LOGGING_GUARD();

        const auto startShift = stream.getPosition();

        IO::BinaryReader reader(stream);
        
        auto signature = reader.readString(4);

        assert(signature == "MPNG");

        auto srcImageWidth = reader.read<uint16_t>();
        auto srcImageHeight = reader.read<uint16_t>();

        auto standardDisplayScale = getStandardDisplayScale();

        auto requiredImageWidth = int(srcImageWidth * standardDisplayScale.x);
        auto requiredImageHeight = int(srcImageHeight * standardDisplayScale.y);

        auto countOfBitmaps = reader.read<uint16_t>();

        // first bitmap size
        auto firstBitmapWidth = reader.read<uint16_t>();
        auto firstBitmapHeight = reader.read<uint16_t>();

        auto prevBitmapFileShift = reader.read<uint32_t>();
        auto prevBitmapDataSize = reader.read<uint32_t>();

        auto maxTextureSize = Common::getImpl<NativeGraphicsInterface>().getMaxTextureSize();

        for (int i = 1; i < countOfBitmaps; ++i)
        {
            auto bitmapWidth = reader.read<uint16_t>();
            auto bitmapHeight = reader.read<uint16_t>();
            auto bitmapFileShift = reader.read<uint32_t>();
            auto bitmapDataSize = reader.read<uint32_t>();

            if ((bitmapWidth < requiredImageWidth || bitmapHeight < requiredImageHeight)
                && bitmapWidth <= maxTextureSize.width && bitmapHeight <= maxTextureSize.height)
            {
                break;
            }

            prevBitmapFileShift = bitmapFileShift;
            prevBitmapDataSize = bitmapDataSize;
        }

        stream.setPosition(startShift + prevBitmapFileShift);
        
        auto nativeTexture = Common::getImpl<NativeGraphicsInterface>().loadTexture(stream, prevBitmapDataSize);
        assert(nativeTexture);
        return std::make_unique<Texture>(
            std::move(nativeTexture),
            Math::Size2DI(srcImageWidth, srcImageHeight),
            Math::RectangleF(0.0f, 0.0f, srcImageWidth / (float)firstBitmapWidth, srcImageHeight / (float)firstBitmapHeight));
    }
}