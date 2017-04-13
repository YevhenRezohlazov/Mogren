#include "FontLoader.h"
#include "Font.h"

#include <Mogren/Framework/Logging/FunctionLoggingGuard.h>

namespace Graphics
{
    namespace Text
    {
        const std::vector<std::string> FontLoader::getResourceExtensions() const
        {
            return{ "mf" };
        }

        std::unique_ptr<ResourceManagement::Resource> FontLoader::loadResource(IO::InputStream & inputStream) const
        {
            DECLARE_FUNCTION_LOGGING_GUARD();
            return Font::loadFromStream(inputStream);
        }
    }
}