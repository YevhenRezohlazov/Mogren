#pragma once

#include <Mogren/Framework/Math/Vector2D.h>
#include <unordered_map>
#include <memory>
#include <vector>

namespace Graphics
{
    class Camera;
    class NativeRenderTarget;

    class RenderTarget
    {
    public:
        ///
        /// Initializes a new instance of the RenderTarget class.
        /// \param nativeRenderTarget The native render target
        ///
        explicit RenderTarget(std::unique_ptr<NativeRenderTarget> nativeRenderTarget);

        
        ///
        /// Gets the native render target instance pointer.
        ///
        const NativeRenderTarget& getNativeRenderTarget() const;

        ///
        /// Gets the render target size.
        ///
        Math::Size2DI getSize() const;

        ///
        /// Returns list of the weak pointers to the cameras attached to this render target
        ///
        const std::vector<std::reference_wrapper<Camera>>& getAttachedCameras() const;

        virtual ~RenderTarget();

    private:
        void attachCamera(Camera &camera);
        void detachCamera(Camera &camera);

        friend class Camera;

    private:
        std::unique_ptr<NativeRenderTarget> mNativeRenderTarget;
        std::vector<std::reference_wrapper<Camera>> mAttachedCameras;
    };
}

