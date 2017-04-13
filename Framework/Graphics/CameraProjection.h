#pragma once

#include "PrimitiveTypes/Viewport.h"

#include <Mogren/Framework/Math/Matrix4x4.h>

namespace Graphics
{
    ///
    /// Interface for camera projection container.
    ///
    class CameraProjection
    {
    public:
        CameraProjection();

        ///
        /// Gets the camera projection matrix.
        ///
        virtual const Math::Matrix4x4& getProjectionMatrix() const;

        ///
        /// Called when camera viewport has been changed.
        ///
        /// \param newViewport The new viewport.
        virtual void updateViewport(Viewport newViewport);

        ///
        /// Returns the current projection transformation version
        /// (call to check whether the projection transformation has been changed since last version)
        ///
        uint64_t getVersion() const;

    protected:
        ///
        /// Increments current projection transformation version.
        /// Should be called every time the projection transformation is changed.
        ///
        void incrementVersion();

    protected:
        Math::Matrix4x4 mProjectionMatrix;

    private:
        ///
        /// Transformation version. Can be used to detect transformation changes.
        ///
        uint64_t mVersion;
    };
}

