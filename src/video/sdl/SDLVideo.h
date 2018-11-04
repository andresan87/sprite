#ifndef SPRITE_PLATFORM_SDLVIDEO_H_
#define SPRITE_PLATFORM_SDLVIDEO_H_

#include "../gl/GLVideo.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#pragma clang diagnostic pop

namespace sprite {

class SDLVideo : public GLVideo
{
	friend class SDLInput;
	static float m_mouseWheel;
	static std::string m_lastCharInput;

	SDL_Window* m_window;
	SDL_GLContext m_glcontext;
	
	bool m_windowHasFocus;
	bool m_windowIsVisible;

public:
	SDLVideo(
		const std::string& title,
		const math::Vector2& resolution,
		const bool fullscreen);
	
	~SDLVideo();

	APP_STATUS HandleEvents();
	
	void EndRendering();

	bool IsSuccessful() const;
};

} // namespace sprite

#endif
