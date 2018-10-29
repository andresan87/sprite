#include "GLVideo.h"

#include "GLInclude.h"

namespace sprite {

GLVideo::GLVideo(const math::Vector2& resolution) :
	m_clearColor(0.0f, 0.0f, 0.0f, 0.0f)
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
	//
}

void GLVideo::SetupSpriteRenderStates()
{
	SetResolution(m_resolution);
	glEnable(GL_DITHER);

	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);

	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glDepthRange(0.0f, 1.0f);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
}

} // namespace sprite
