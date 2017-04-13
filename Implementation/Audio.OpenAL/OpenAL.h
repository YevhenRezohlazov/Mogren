#pragma once

#include "ALInclude.h"

namespace Audio
{
    class OpenAL
    {
    private:
        // disallow creating instance
        OpenAL();

        static ALCdevice *mDevice;
        static ALCcontext *mContext;
    public:
        ///
        /// Initializes OpenAL context. Should be called once from main app thread
        ///
        static void initialize();

        ///
        /// Destroys OpenAL context. Should be called once from main app thread
        ///
        static void destroy();
    };
}

