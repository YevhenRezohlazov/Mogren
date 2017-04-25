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
    };
}
