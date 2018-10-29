#ifndef SPRITE_PLATFORM_GLSHADER_H_
#define SPRITE_PLATFORM_GLSHADER_H_

#include "../Shader.h"

#include "GLInclude.h"

namespace sprite {

class GLShader : public Shader
{
	GLuint m_shaderProgram;

public:
	GLShader(
		const VideoPtr& video,
		const std::string& vertexShaderSource,
		const std::string& fragmentShaderSource);

	GLuint GetShaderProgram() const;
};

} // namespace sprite

#endif
