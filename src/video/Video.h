#ifndef SPRITE_PLATFORM_VIDEO_H_
#define SPRITE_PLATFORM_VIDEO_H_

#include <memory>
#include <string>

#include "../math/Vector2.h"

namespace sprite {

class Video;

typedef std::shared_ptr<Video> VideoPtr;

class Video
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

	static VideoPtr Create(
		const std::string& title,
		const math::Vector2& resolution,
		const bool fullscreen);

	virtual void Log(const std::string& message, const LOG_MESSAGE_TYPE type) = 0;
	virtual APP_STATUS HandleEvents() = 0;
};

} // namespace sprite

#endif
