#pragma once

#include "InputStream.h"

#include <vector>
#include <string>

namespace IO
{
    class BinaryReader
    {
    private:
        InputStream & mInputStream;

    public:
        explicit BinaryReader(InputStream &inputStream);

        template <typename TItem>
        TItem read();

        template <typename TItem>
        std::vector<TItem> readList(int countItems);

        std::string readString(uint32_t bytesCount);
    };

    template<typename TItem>
    inline TItem BinaryReader::read()
    {
        TItem res;
        mInputStream.read(&res, sizeof(TItem));
        return res;
    }

    template<typename TItem>
    inline std::vector<TItem> BinaryReader::readList(int countItems)
    {
        std::vector<TItem> res;
        res.resize(countItems);
        mInputStream.read(res.data(), sizeof(TItem) * countItems);
        return res;
    }
}
