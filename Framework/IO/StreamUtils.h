#pragma once

#include "InputStream.h"
#include "OutputStream.h"

namespace IO
{
    void copyStream(InputStream &source, OutputStream &destination, uint32_t bufferSize = 32768);
}
