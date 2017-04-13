#include "OpenALAudioImpl.h"
#include "OpenAL.h"
#include "ALSound.h"

namespace Audio
{
    OpenALAudioImpl::OpenALAudioImpl()
    {
        OpenAL::initialize();
    }

    std::unique_ptr<NativeSound> OpenALAudioImpl::createSound(IO::InputStream & stream)
    {
        return ALSound::load(stream);
    }

    OpenALAudioImpl::~OpenALAudioImpl()
    {
        OpenAL::destroy();
    }
}