#include "GLVideo.h"

#include "GLInclude.h"

namespace sprite {

GLVideo::GLVideo(const math::Vector2& resolution)
{
	m_resolution = resolution;
}

void GLVideo::SetResolution(const math::Vector2& resolution)
{
	m_resolution = resolution;
	glViewport(0, 0, (GLsizei)resolution.x, (GLsizei)resolution.y);
}

void GLVideo::SetupSpriteRenderStates()
{
	SetResolution(m_resolution);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glDepthRange(0.0f, 1.0f);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
}

} // namespace sprite
