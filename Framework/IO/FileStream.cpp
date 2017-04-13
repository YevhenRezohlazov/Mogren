#include "FileStream.h"
#include <assert.h>

namespace IO
{
    FileStream::FileStream(FileStream&& other)
        : mFile(other.mFile), mFileMode(other.mFileMode)
    {
        other.mFile = nullptr;
    }

    FileStream::FileStream(const std::string& fileName, FileMode fileMode)
        : mFileMode(fileMode)
    {
        const char *mode;

        switch (fileMode)
        {
        case IO::FileMode::ReadText:
            mode = "r";
            break;
        case IO::FileMode::WriteText:
            mode = "w";
            break;
        case IO::FileMode::AppendText:
            mode = "a";
            break;
        case IO::FileMode::ReadBinary:
            mode = "rb";
            break;
        case IO::FileMode::WriteBinary:
            mode = "wb";
            break;
        case IO::FileMode::AppendBinary:
            mode = "ab";
            break;
        case IO::FileMode::ReadUpdateText:
            mode = "r+";
            break;
        case IO::FileMode::WriteUpdateText:
            mode = "w+";
            break;
        case IO::FileMode::AppendUpdateText:
            mode = "a+";
            break;
        case IO::FileMode::ReadUpdateBinary:
            mode = "r+b";
            break;
        case IO::FileMode::WriteUpdateBinary:
            mode = "w+b";
            break;
        case IO::FileMode::AppendUpdateBinary:
            mode = "a+b";
            break;
        default:
            mode = "";
            break;
        }

        mFile = std::fopen(fileName.c_str(), mode);
    }

    FileStream::~FileStream()
    {
        if (mFile != nullptr) std::fclose(mFile);
    }

    bool FileStream::canRead() const
    {
        switch (mFileMode)
        {
        case IO::FileMode::ReadText:
        case IO::FileMode::ReadBinary:
        case IO::FileMode::ReadUpdateText:
        case IO::FileMode::WriteUpdateText:
        case IO::FileMode::AppendUpdateText:
        case IO::FileMode::ReadUpdateBinary:
        case IO::FileMode::WriteUpdateBinary:
        case IO::FileMode::AppendUpdateBinary:
            return mFile != nullptr;
        default:
            return false;
        }
    }

    uint32_t FileStream::read(void *buffer, uint32_t count)
    {
        if (canRead())
        {
            return std::fread(buffer, 1, count, mFile);
        }

        return 0;
    }

    void FileStream::setPosition(uint32_t position)
    {
        std::fseek(mFile, position, SEEK_SET);
    }

    uint32_t FileStream::getPosition() const
    {
        return std::ftell(mFile);
    }

    uint32_t FileStream::getLength() const
    {
        uint32_t pos = std::ftell(mFile);
        std::fseek(mFile, 0, SEEK_END);
        uint32_t size = std::ftell(mFile);
        std::fseek(mFile, pos, SEEK_SET);
        return size;
    }

    bool FileStream::canWrite() const
    {
        switch (mFileMode)
        {
        case IO::FileMode::WriteText:
        case IO::FileMode::AppendText:
        case IO::FileMode::WriteBinary:
        case IO::FileMode::AppendBinary:
        case IO::FileMode::ReadUpdateText:
        case IO::FileMode::WriteUpdateText:
        case IO::FileMode::AppendUpdateText:
        case IO::FileMode::ReadUpdateBinary:
        case IO::FileMode::WriteUpdateBinary:
        case IO::FileMode::AppendUpdateBinary:
            return mFile != nullptr;
        default:
            return false;
        }
    }

    uint32_t FileStream::write(const void *buffer, uint32_t count)
    {
        if (canWrite())
        {
            return std::fwrite(buffer, 1, count, mFile);
        }

        return 0;
    }

    FileStream& FileStream::operator=(FileStream&& other)
    {
        mFile = other.mFile;
        mFileMode = other.mFileMode;
        other.mFile = nullptr;
        return *this;
    }
}