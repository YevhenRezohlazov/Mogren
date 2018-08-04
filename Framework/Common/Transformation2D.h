#pragma once

#include "Transformation.h"

#include <Mogren/Framework/Math/Vector2D.h>

namespace Common
{
    ///
    /// Two-dimensional transformation
    ///
    class Transformation2D : public Transformation
    {
    public:
        ///
        /// Initializes a new instance of the Transformation2D class.
        ///
        Transformation2D();

        ///
        /// Gets or sets the position.
        ///
        Math::Vector2DF getPosition() const;

        ///
        /// Gets or sets the position.
        ///
        Transformation2D& setPosition(const Math::Vector2DF& position);

        ///
        /// Gets the rotation angle (in radians).
        ///
        float getRotationAngle() const;

        ///
        /// Gets the rotation angle (in radians).
        ///
        Transformation2D& setRotationAngle(float angle);

        ///
        /// Gets the scale factors.
        ///
        Math::Vector2DF getScale() const;

        ///
        /// Sets the scale factors.
        ///
        Transformation2D& setScale(const Math::Vector2DF &scale);

        ///
        /// Creates a copy of the transformation instance
        ///
        std::unique_ptr<Transformation> clone() const override;

    private:
        ///
        /// The rotation angle (in radians)
        ///
        float mRotationAngle;

        ///
        /// The scale factors
        ///
        Math::Vector2DF mScale;
    };
}

