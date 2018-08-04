#pragma once

#include <Mogren/Framework/Math/Matrix4x4.h>
#include <memory>

namespace Common
{
    ///
    /// Base transformation class
    ///
    class Transformation
    {
    public:
        ///
        /// Creates empty transformation (identity matrix)
        ///
        Transformation();

        ///
        /// Gets the transformation matrix.
        ///
        virtual const Math::Matrix4x4& getMatrix() const;

        ///
        /// Returns the current transformation version
        /// (call to check whether the transformation has been changed since last version)
        ///
        const uint64_t& getVersion() const;

        ///
        /// Creates a copy of the transformation instance
        ///
        virtual std::unique_ptr<Transformation> clone() const;

        virtual ~Transformation() = default;

    protected:
        ///
        /// Increments current transformation version.
        /// Should be called every time the transformation is changed.
        ///
        void incrementVersion();

    private:
        ///
        /// Transformation version. Can be used to detect transformation changes.
        ///
        uint64_t mVersion;

    protected:
        ///
        /// Transformation matrix
        ///
        Math::Matrix4x4 mMatrix;
    };
}

