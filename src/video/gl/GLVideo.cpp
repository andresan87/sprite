#include "GLVideo.h"

#include "GLInclude.h"

#include <sstream>

namespace sprite {

GLVideo::GLVideo(const math::Vector2& resolution) :
	m_alphaMode(AM_UNKNOWN),
	m_clearColor(0.0f, 0.0f, 0.0f, 0.0f),
	m_logger(Logger::Create())
{
	m_resolution = resolution;
}

void GLVideo::SetResolution(const math::Vector2& resolution)
{
	m_resolution = resolution;
	glViewport(0, 0, (GLsizei)resolution.x, (GLsizei)resolution.y);
}

math::Vector2 GLVideo::GetResolution() const
{
	return m_resolution;
}

void GLVideo::SetClearColor(const Color& color)
{
	m_clearColor = color;
}

Color GLVideo::GetClearColor() const
{
	return m_clearColor;
}

void GLVideo::BeginRendering()
{
	glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLVideo::EndRendering()
{
	#if DEBUG
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			std::stringstream ss; ss << "OpenGL error: " << err;
			m_logger->Log(ss.str(), Logger::LMT_ERROR);
		}
	#endif
}

void GLVideo::SetupSpriteRenderStates()
{
	SetResolution(m_resolution);
	glEnable(GL_DITHER);

	glDisable(GL_CULL_FACE);

	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glDepthRange(0.0f, 1.0f);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	SetAlphaMode(AM_PIXEL);
}

void GLVideo::SetAlphaMode(const ALPHA_MODE mode)
{
	m_alphaMode = mode;
	switch(mode)
	{
		case AM_ADD:
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			break;
		case AM_MODULATE:
			glEnable(GL_BLEND);
			glBlendFunc(GL_ZERO, GL_SRC_COLOR);
			break;
		case AM_NONE:
			glDisable(GL_BLEND);
			break;
		case AM_PIXEL:
		default:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
	};
}

Video::ALPHA_MODE GLVideo::GetAlphaMode() const
{
	return m_alphaMode;
}

void GLVideo::Log(const std::string& message, const Logger::LOG_MESSAGE_TYPE type)
{
	m_logger->Log(message, type);
}

} // namespace sprite
