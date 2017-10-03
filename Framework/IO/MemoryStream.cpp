#include "MemoryStream.h"
#include <Mogren/Framework/Math/Functions.h>
#include <cstring>

namespace IO
{
    MemoryStream::MemoryStream(uint32_t initialCapacity /*= 0*/)
        : mBuffer(), mPosition(0)
    {
        mBuffer.reserve(initialCapacity);
    }

    MemoryStream::MemoryStream(const void *initialData, uint32_t initialDataSize)
        : mBuffer(), mPosition(0)
    {
        write(initialData, initialDataSize);
        setPosition(0);
    }

    MemoryStream::MemoryStream(MemoryStream&& other)
        : mBuffer(std::move(other.mBuffer)), mPosition(other.mPosition)
    {
    }

    const char* MemoryStream::getData() const
    {
        return mBuffer.capacity() > 0 ? &mBuffer.front() : nullptr;
    }

    char* MemoryStream::getData()
    {
        return mBuffer.capacity() > 0 ? &mBuffer.front() : nullptr;
    }

    bool MemoryStream::canRead() const
    {
        return mPosition < mBuffer.size();
    }

    uint32_t MemoryStream::read(void *buffer, uint32_t count)
    {
        auto toRead = Math::minimum(static_cast<uint32_t>(mBuffer.size()) - mPosition, count);
        if (toRead > 0)
        {
            memcpy(buffer, getData() + mPosition, toRead);
            mPosition += toRead;
        }
        return toRead;
    }

    void MemoryStream::setPosition(uint32_t position)
    {
        mPosition = Math::minimum(position, static_cast<uint32_t>(mBuffer.size()));
    }

    uint32_t MemoryStream::getPosition() const
    {
        return mPosition;
    }

    uint32_t MemoryStream::getLength() const
    {
        return mBuffer.size();
    }

    bool MemoryStream::canWrite() const
    {
        return true;
    }

    uint32_t MemoryStream::write(const void *buffer, uint32_t count)
    {
        if (canWrite())
        {
            mBuffer.resize(Math::maximum(static_cast<uint32_t>(mBuffer.size()), mPosition + count));
            memcpy(getData() + mPosition, buffer, count);
            mPosition += count;
            return count;
        }

        return 0;
    }

    MemoryStream MemoryStream::clone() const
    {
        return MemoryStream(getData(), mBuffer.size());
    }

    MemoryStream& MemoryStream::operator=(MemoryStream &&other)
    {
        mBuffer = std::move(other.mBuffer);
        mPosition = other.mPosition;
        return *this;
    }
}
