#pragma once

#include <Mogren/Framework/Math/Vector2D.h>
#include <Mogren/Framework/Math/Rectangle.h>
#include <Mogren/Framework/ResourceManagement/Resource.h>
#include <memory>

namespace Graphics
{
    class NativeTexture;
    ///
    /// Texture class
    ///
    class Texture : public ResourceManagement::Resource
    {
    public:
        ///
        /// Initializes a new instance of the Texture class.
        ///
        /// \param nativeTexture The native texture instance.
        Texture(std::unique_ptr<NativeTexture> nativeTexture);

        ///
        /// Initializes a new instance of the Texture class.
        ///
        /// \param nativeTexture The native texture instance.
        /// \param size Overridden texture size.
        /// \param originalTextureRect Original texture rectangle
        /// (in texture coords space) for nearest neightbour textures
        Texture(
            std::unique_ptr<NativeTexture> nativeTexture,
            const Math::Size2DI & size,
            const Math::RectangleF & originalTextureRect);

        ///
        /// Initializes a new instance of the Texture class.
        ///
        /// \param size Texture size.
        /// \param data Texture data. width * height * 4 bytes, RGBA
        explicit Texture(const Math::Size2DI & size, const uint8_t * data, bool autoFinalize = true);

        ///
        /// Gets the native texture instance.
        ///
        const NativeTexture &getNativeTexture() const;

        ///
        /// Gets the texture size (may differ from native texture size).
        ///
        const Math::Size2DI& getSize() const;

        ///
        /// Gets the original texture rectangle
        /// (in texture coords space) for nearest neightbour textures
        ///
        const Math::RectangleF getOriginalTextureRect() const;

        virtual ~Texture();

    protected:
        virtual void finalize() override;

    private:
        std::unique_ptr<NativeTexture> mNativeTexture;
        Math::Size2DI mSize;
        Math::RectangleF mOriginalTextureRect;
    };
}

