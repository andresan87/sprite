#ifndef SPRITE_VIDEO_GLVIDEO_H_
#define SPRITE_VIDEO_GLVIDEO_H_

#include "../Video.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#pragma clang diagnostic pop

namespace sprite {

class GLVideo : public Video
{
public:
	GLVideo(const math::Vector2& resolution);
};

} // namespace sprite

#endif
