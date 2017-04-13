#include "Transformation.h"

namespace Common
{
    Transformation::Transformation() : mVersion(0), mMatrix(Math::Matrix4x4::Identity)
    {
    }

    const uint64_t& Transformation::getVersion() const
    {
        return mVersion;
    }

    void Transformation::incrementVersion()
    {
        mVersion += 1;
    }

    const Math::Matrix4x4& Transformation::getMatrix() const
    {
        return mMatrix;
    }
}