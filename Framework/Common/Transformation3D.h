#pragma once

#include "Transformation.h"

#include <Mogren/Framework/Math/Vector3D.h>

namespace Common
{
    ///
    /// Three-dimensional transformation
    ///
    class Transformation3D : public Transformation
    {
    public:
        ///
        /// Initializes a new instance of the Transformation2D class.
        ///
        Transformation3D();

        ///
        /// Gets or sets the position.
        ///
        Math::Vector3DF getPosition() const;

        ///
        /// Gets or sets the position.
        ///
        Transformation3D& setPosition(const Math::Vector3DF& position);

        Transformation3D& setRotation(const Math::Vector3DF& pitchYawRoll);

        Transformation3D& setRotation(const Math::Vector3DF& axis, float angle);

        Transformation3D& setScale(const Math::Vector3DF& scale);

        Math::Vector3DF getScale() const;

        ///
        /// Creates a copy of the transformation instance
        ///
        std::unique_ptr<Transformation> clone() const override;

    private:
        Math::Vector3DF mScale = Math::Vector3DF(1.0f);
    };
}
