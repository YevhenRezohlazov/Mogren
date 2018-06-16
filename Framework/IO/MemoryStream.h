#pragma once

#include "InputStream.h"
#include "OutputStream.h"

#include <vector>

namespace IO
{
    ///
    /// Stream with data stored in RAM
    ///
    class MemoryStream : public InputStream, public OutputStream
    {
    public:
        explicit MemoryStream(uint32_t initialCapacity = 0);

        MemoryStream(const void *initialData, uint32_t initialDataSize);

        MemoryStream(MemoryStream&& other);

        MemoryStream& operator=(MemoryStream &&other);

        const char* getData() const;

        char* getData();

        template <typename T>
        const T* getData() const;

        template <typename T>
        T* getData();

        virtual bool canRead() const override;

        virtual uint32_t read(void *buffer, uint32_t count) override;

        virtual void setPosition(uint32_t position) override;

        virtual uint32_t getPosition() const override;

        virtual uint32_t getLength() const override;

        virtual bool canWrite() const override;

        MemoryStream clone() const;

        virtual uint32_t write(const void *buffer, uint32_t count) override;

        void resize(uint32_t newSize);

    private:
        std::vector<char> mBuffer;
        uint32_t mPosition;
    };

    template<typename T>
    inline const T * MemoryStream::getData() const
    {
        return reinterpret_cast<const T*>(getData());
    }
    template<typename T>
    inline T * MemoryStream::getData()
    {
        return reinterpret_cast<T*>(getData());
    }
}
