#ifndef SPRITE_PLATFORM_SDLVIDEO_H_
#define SPRITE_PLATFORM_SDLVIDEO_H_

#include "../Video.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#pragma clang diagnostic pop

namespace sprite {

class SDLVideo : public Video
{
	SDL_Window* m_window;
	SDL_GLContext m_glcontext;
	
	bool m_windowHasFocus;
	bool m_windowIsVisible;
	
	float m_mouseWheel;
	
	std::string m_lastCharInput;

public:
	SDLVideo(
		const std::string& title,
		const math::Vector2& resolution,
		const bool fullscreen);

	APP_STATUS HandleEvents();

	void Log(const std::string& message, const LOG_MESSAGE_TYPE type);

	bool IsSuccessful() const;
};

} // namespace sprite

#endif
