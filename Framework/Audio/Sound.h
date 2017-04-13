#pragma once

#include <Mogren/Framework/ResourceManagement/Resource.h>
#include <memory>

namespace Audio
{
    class NativeSound;
    class SoundPlayer;

    ///
    /// The sound player class
    ///
    class Sound : public ResourceManagement::Resource
    {
    public:
        ///
        /// Initializes a new instance of SoundPlayer class.
        ///
        explicit Sound(std::unique_ptr<NativeSound> nativeSound);

        virtual float getDuration() const;

        ~Sound();

    protected:
        virtual void finalize() override;

    private:
        friend class SoundPlayer;
        std::unique_ptr<NativeSound> mNativeSound;
    };
}

