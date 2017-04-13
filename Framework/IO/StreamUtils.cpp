#include "StreamUtils.h"

namespace IO
{
    void copyStream(InputStream &source, OutputStream &destination, uint32_t bufferSize /*= 32768*/)
    {
        char *buf = new char[bufferSize];

        while (source.canRead())
        {
            auto bytesRead = source.read(buf, bufferSize);

            if (bytesRead == 0)
            {
                break;
            }

            destination.write(buf, bytesRead);
        }

        delete[] buf;
    }
}