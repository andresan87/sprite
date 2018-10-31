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
	math::Vector2 m_resolution;
	Color m_clearColor;

	ALPHA_MODE m_alphaMode;

public:
	GLVideo(const math::Vector2& resolution);

	void SetClearColor(const Color& color);
	Color GetClearColor() const;

	void BeginRendering();
	void EndRendering();

	void SetAlphaMode(const ALPHA_MODE mode);
	ALPHA_MODE GetAlphaMode() const;

	void SetResolution(const math::Vector2& resolution);
	math::Vector2 GetResolution() const;

	void SetupSpriteRenderStates();
};

} // namespace sprite

#endif
