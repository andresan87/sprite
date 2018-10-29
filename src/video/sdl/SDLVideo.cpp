#include "SDLVideo.h"

#include <iostream>

namespace sprite {

VideoPtr Video::Create(
	const std::string& title,
	const math::Vector2& resolution,
	const bool fullscreen)
{
	std::shared_ptr<SDLVideo> r = std::make_shared<SDLVideo>(title, resolution, fullscreen);
	return r->IsSuccessful() ? r : VideoPtr();
}

SDLVideo::SDLVideo(
	const std::string& title,
	const math::Vector2& resolution,
	const bool fullscreen) :
	GLVideo(resolution),
	m_windowHasFocus(false),
	m_windowIsVisible(false),
	m_mouseWheel(0.0f)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		Log("SDL initialization failed", Video::LMT_ERROR);
		return;
	}

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	if (fullscreen)
	{
		flags |= SDL_WINDOW_FULLSCREEN | SDL_WINDOW_BORDERLESS;
	}

	if ((m_window = SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			static_cast<int>(resolution.x),
			static_cast<int>(resolution.y),
			flags)) != NULL)
	{

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_glcontext = SDL_GL_CreateContext(m_window);
	}
	else
	{
		SDL_Quit();
		return;
	}

	SDL_GL_SetSwapInterval(1);
	
	SetupSpriteRenderStates();
}

SDLVideo::~SDLVideo()
{
	SDL_GL_DeleteContext(m_glcontext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

Video::APP_STATUS SDLVideo::HandleEvents()
{
	APP_STATUS r = AS_OK;

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					m_windowHasFocus = true;
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					m_windowHasFocus = false;
					break;
				case SDL_WINDOWEVENT_SHOWN:
					m_windowIsVisible = true;
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					m_windowIsVisible = false;
					break;
			}
			break;
		case SDL_QUIT:
			r = AS_QUIT;
			break;
		case SDL_MOUSEWHEEL:
				m_mouseWheel = static_cast<float>(event.wheel.y);
			break;
		case SDL_TEXTINPUT:
			m_lastCharInput = event.text.text;
			break;
		}
	}

	if (!m_windowIsVisible)
		r = AS_SKIP;

	return r;
}

void SDLVideo::EndRendering()
{
	GLVideo::EndRendering();
	SDL_GL_SwapWindow(m_window);
}

void SDLVideo::Log(const std::string& message, const Video::LOG_MESSAGE_TYPE type)
{
	if (type == Video::LMT_ERROR)
	{
		std::cerr << "ERROR" << " " << message << std::endl;
	}
	else
	{
		std::cout << message << std::endl;
	}
}

bool SDLVideo::IsSuccessful() const
{
	return (m_window != NULL);
}

} // namespace sprite
