#ifndef SPRITE_PLATFORM_APPLICATION_H_
#define SPRITE_PLATFORM_APPLICATION_H_

#include <memory>
#include <string>

namespace sprite {

class Application;

typedef std::shared_ptr<Application> ApplicationPtr;

class Application
{
public:
	enum LOG_MESSAGE_TYPE
	{
		LMT_INFO,
		LMT_WARNING,
		LMT_ERROR
	};

	enum APP_STATUS
	{
		AS_OK,
		AS_QUIT,
		AS_SKIP
	};

	virtual void Log(const std::string& message, const LOG_MESSAGE_TYPE type) = 0;
	virtual APP_STATUS HandleEvents() = 0;
};

} // namespace sprite

#endif
