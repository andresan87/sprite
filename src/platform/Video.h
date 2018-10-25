#ifndef SPRITE_PLATFORM_VIDEO_H_
#define SPRITE_PLATFORM_VIDEO_H_

#include <memory>
#include <string>

#include "Application.h"

#include "../math/Vector2.h"

namespace sprite {

class Video;

typedef std::shared_ptr<Video> VideoPtr;

class Video : public Application
{
public:
	static VideoPtr Create(
		const std::string& title,
		const math::Vector2& resolution,
		const bool fullscreen);
};

} // namespace sprite

#endif
