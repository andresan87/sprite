#ifndef SPRITE_PLATFORM_GLSHADER_H_
#define SPRITE_PLATFORM_GLSHADER_H_

#include "../Shader.h"

#include "GLInclude.h"

namespace sprite {

class GLShader : public Shader
{
	GLuint m_program;

	tsl::hopscotch_map<std::string, GLint> m_parameters;

	GLint FindUniformLocation(const std::string& name);

public:
	GLShader(
		const VideoPtr& video,
		const std::string& vertexShaderSource,
		const std::string& fragmentShaderSource);

	void SetShader();

	void SetParameter(const std::string& name, const float v);
	void SetParameter(const std::string& name, const math::Vector2& v);
	void SetParameter(const std::string& name, const math::Vector3& v);
	void SetParameter(const std::string& name, const math::Vector4& v);
	void SetParameter(const std::string& name, TexturePtr texture, const unsigned int index);
	void SetConstantArray(const std::string& name, unsigned int nElements, const math::Vector4* v);
};

} // namespace sprite

#endif
