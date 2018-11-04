#ifndef PLATFORM_LOGGER_H_
#define PLATFORM_LOGGER_H_

#include <memory>

namespace sprite {

class Logger;

typedef std::shared_ptr<Logger> LoggerPtr;

class Logger
{
public:
	enum LOG_MESSAGE_TYPE
	{
		LMT_INFO,
		LMT_WARNING,
		LMT_ERROR
	};

	static LoggerPtr Create();

	virtual void Log(const std::string& message, const LOG_MESSAGE_TYPE type) = 0;
};

} // namespace sprite

#endif
