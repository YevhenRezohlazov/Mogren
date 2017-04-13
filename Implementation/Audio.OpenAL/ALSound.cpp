#include "ALSound.h"
#include "ALSoundPlayer.h"
#include <Mogren/Framework/App/App.h>
#include <Mogren/Framework/IO/InputStream.h>
#include <Mogren/Framework/IO/BinaryReader.h>
#include <Mogren/Framework/IO/MemoryStream.h>
#include <Mogren/Framework/IO/StreamUtils.h>
#include <Mogren/Framework/Logging/Logger.h>
#include <Mogren/ThirdParty/stb_vorbis/stb_vorbis.h>
#include <assert.h>

namespace Audio
{
    namespace
    {
        ALenum to_al_format(short channels, short samples)
        {
            bool stereo = (channels > 1);

            switch (samples) {
            case 16:
                if (stereo)
                    return AL_FORMAT_STEREO16;
                else
                    return AL_FORMAT_MONO16;
            case 8:
                if (stereo)
                    return AL_FORMAT_STEREO8;
                else
                    return AL_FORMAT_MONO8;
            default:
                return -1;
            }
        }
    }

    ALSound::ALSound()
    {
    }

    std::unique_ptr<ALSound> ALSound::load(IO::InputStream &stream)
    {
        IO::BinaryReader reader(stream);
        auto initialStreamPos = stream.getPosition();
        auto format = reader.readString(4);
        stream.setPosition(initialStreamPos);

        if (format == "OggS")
        {
            return loadOgg(stream);
        }
        else if (format == "RIFF")
        {
            return loadWAV(stream);
        }
        else
        {
            assert(false && "Not a WAV nor OGG file.");
            return nullptr;
        }
    }

    std::unique_ptr<NativeSoundPlayer> ALSound::createSoundPlayer() const
    {
        return std::make_unique<ALSoundPlayer>(*this);
    }

    float ALSound::getDuration() const
    {
        return mDuration;
    }

    ALuint ALSound::getBuffer() const
    {
        return mBuffer;
    }

    void ALSound::finalize()
    {
        alGenBuffers(1, &mBuffer);
        alBufferData(mBuffer, mSourceFormat, mSourceBuffer.data(), mSourceBuffer.size(), mSampleRate);
        mSourceBuffer.clear();
        mSourceBuffer.shrink_to_fit();
    }

    std::unique_ptr<ALSound> ALSound::loadWAV(IO::InputStream &stream)
    {
        IO::BinaryReader reader(stream);

        reader.read<int32_t>();
        reader.read<int32_t>();

        if (reader.readString(8) != "WAVEfmt ")
            assert(false && "Not a WAV file");

        int subChunkSize = reader.read<int32_t>();
        reader.read<int16_t>(); // audioFormat
        short channels = reader.read<int16_t>();
        int sampleRate = reader.read<int32_t>();;
        int byteRate = reader.read<int32_t>();;
        reader.read<int16_t>();
        short bitsPerSample = reader.read<int16_t>();

        if (subChunkSize > 16) {
            short extraParams = reader.read<int16_t>();
            reader.readString(extraParams);
        }

        if (reader.readString(4) != "data")
            assert(false && "Not a WAV file");

        std::unique_ptr<ALSound> res(new ALSound);
        int bufferSize = reader.read<int32_t>();

        std::vector<char> buffer(bufferSize);
        stream.read(buffer.data(), bufferSize);

        res->mDuration = float(bufferSize) / byteRate;
        res->mSourceBuffer = std::move(buffer);
        res->mSourceFormat = to_al_format(channels, bitsPerSample);
        res->mSampleRate = sampleRate;

        Logging::Logger::writeInfo("Loaded WAV file.");
        return res;
    }

    std::unique_ptr<ALSound> ALSound::loadOgg(IO::InputStream &stream)
    {
        IO::MemoryStream memoryStream;
        IO::copyStream(stream, memoryStream, stream.getLength());

        stb_vorbis *oggData = stb_vorbis_open_memory((unsigned char*)memoryStream.getData(), memoryStream.getLength(), nullptr, nullptr);
        stb_vorbis_info oggInfo = stb_vorbis_get_info(oggData);

        std::unique_ptr<ALSound> res(new ALSound);

        const unsigned int totalSampleCount = stb_vorbis_stream_length_in_samples(oggData) * oggInfo.channels;

        std::vector<char> buffer(totalSampleCount * sizeof(short));
        int countSamplesRead = stb_vorbis_get_samples_short_interleaved(oggData, oggInfo.channels, (short*)buffer.data(), totalSampleCount);

        res->mDuration = stb_vorbis_stream_length_in_seconds(oggData);
        res->mSourceFormat = to_al_format(oggInfo.channels, 16);
        res->mSampleRate = oggInfo.sample_rate;
        res->mSourceBuffer = std::move(buffer);

        Logging::Logger::writeInfo("Loaded OGG file");
        return res;
    }

    ALSound::~ALSound()
    {
         alDeleteBuffers(1, &mBuffer);
    }
}