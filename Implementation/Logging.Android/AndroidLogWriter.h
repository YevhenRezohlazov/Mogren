#pragma once

#include <Mogren/Framework/Logging/LogWriter.h>

namespace Logging
{
	class AndroidLogWriter : public Logging::LogWriter
	{
	public:
		///
		/// Writes the informational message into the log.
		///
		/// \param message The log message to be written.
		virtual void write(const char * message) override;
	};
}
