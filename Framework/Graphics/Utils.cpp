#include "Utils.h"
#include <Mogren/Framework/Common/ImplementationProvider.h>
#include <Mogren/Framework/Common/NativeInterface/NativeCoreInterface.h>
#include "NativeInterface/NativeRenderTarget.h"

namespace Graphics
{
    Math::Vector2DF getStandardDisplayScale()
    {
        auto widthRel = Common::getImpl<Common::NativeCoreInterface>().getScreenSize().x / 2560.0f;
        auto heightRel = Common::getImpl<Common::NativeCoreInterface>().getScreenSize().y / 1600.0f;

        return Math::Vector2DF(widthRel, heightRel);
    }
}