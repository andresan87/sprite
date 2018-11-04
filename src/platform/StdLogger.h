#ifndef PLATFORM_STD_LOGGER_H_
#define PLATFORM_STD_LOGGER_H_

#include "Logger.h"

namespace sprite {

class StdLogger : public Logger
{
public:
	void Log(const std::string& message, const Logger::LOG_MESSAGE_TYPE type);
};

} // namespace sprite

#endif
