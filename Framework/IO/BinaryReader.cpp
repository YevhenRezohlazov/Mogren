#include "BinaryReader.h"

namespace IO
{
    BinaryReader::BinaryReader(InputStream &inputStream)
        : mInputStream(inputStream)
    {
    }

    std::string BinaryReader::readString(uint32_t bytesCount)
    {
        std::string res;
        res.resize(bytesCount);
        mInputStream.read(const_cast<char*>(res.c_str()), bytesCount);
        return res;
    }
}