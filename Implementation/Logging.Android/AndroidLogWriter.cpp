#include "AndroidLogWriter.h"
#include <android/log.h>

namespace Logging
{
	void AndroidLogWriter::write(const char * message)
	{
        __android_log_write(ANDROID_LOG_INFO, "Mogren", message);
	}
}
