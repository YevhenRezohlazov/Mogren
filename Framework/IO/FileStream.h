#pragma once

#include "InputStream.h"
#include "OutputStream.h"

#include <string>
#include <cstdio>

namespace IO
{
    ///
    /// File opening modes
    ///
    enum class FileMode
    {
        ReadText,
        WriteText,
        AppendText,
        ReadBinary,
        WriteBinary,
        AppendBinary,
        ReadUpdateText,
        WriteUpdateText,
        AppendUpdateText,
        ReadUpdateBinary,
        WriteUpdateBinary,
        AppendUpdateBinary
    };

    ///
    /// File stream
    ///
    class FileStream : public InputStream, public OutputStream
    {
    public:
        FileStream(const std::string& fileName, FileMode fileMode);

        FileStream(FileStream&& other);
        FileStream& operator=(FileStream&&);

        ~FileStream();

        virtual bool canRead() const override;

        virtual uint32_t read(void *buffer, uint32_t count) override;

        virtual void setPosition(uint32_t position) override;

        virtual uint32_t getPosition() const override;

        virtual uint32_t getLength() const override;

        virtual bool canWrite() const override;

        virtual uint32_t write(const void *buffer, uint32_t count) override;

    private:
        FILE *mFile;
        FileMode mFileMode;
    };
}
