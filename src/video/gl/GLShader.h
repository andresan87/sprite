#ifndef SPRITE_PLATFORM_GLSHADER_H_
#define SPRITE_PLATFORM_GLSHADER_H_

#include "../Shader.h"

#include "GLInclude.h"

#include "../../utilities/tsl/hopscotch_map.h"

namespace sprite {

class GLShader : public Shader
{
	GLuint m_shaderProgram;
	
	tsl::hopscotch_map<std::string, GLint> m_parameters;
	tsl::hopscotch_map<std::string, GLint> m_textureParamsIndices;

	GLint FindUniformLocation(const std::string& name, const bool isTexture);
	
	unsigned int m_textureCount;

public:
	GLShader(
		const VideoPtr& video,
		const std::string& vertexShaderSource,
		const std::string& fragmentShaderSource);

	GLuint GetShaderProgram() const;

	void SetParameter(const std::string& name, const float v);
	void SetParameter(const std::string& name, const math::Vector2& v);
	void SetParameter(const std::string& name, const math::Vector3& v);
	void SetParameter(const std::string& name, const math::Vector4& v);
	void SetParameter(const std::string& name, TexturePtr texture);
};

} // namespace sprite

#endif
