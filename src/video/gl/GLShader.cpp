#include "GLShader.h"

#include "GLTexture.h"

#define MAX_MESSAGE_SIZE 1024

namespace sprite {

ShaderPtr Shader::Create(
	const VideoPtr& video,
	const std::string& vertexShaderSource,
	const std::string& fragmentShaderSource)
{
	return std::make_shared<GLShader>(video, vertexShaderSource, fragmentShaderSource);
}

GLShader::GLShader(
	const VideoPtr& video,
	const std::string& vertexShaderSource,
	const std::string& fragmentShaderSource) :
	m_shaderProgram(0),
	m_textureCount(0)
{
	const char* vertexShaderCstr   = vertexShaderSource.c_str();
	const char* fragmentShaderCstr = fragmentShaderSource.c_str();

	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCstr, NULL);
	glCompileShader(vertexShader);

	GLint success;
	char infoLog[MAX_MESSAGE_SIZE];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, MAX_MESSAGE_SIZE, NULL, infoLog);
		video->Log("glCompileShader vertex: " + std::string(infoLog), Video::LMT_ERROR);
	}

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCstr, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, MAX_MESSAGE_SIZE, NULL, infoLog);
		video->Log("glCompileShader fragment: " + std::string(infoLog), Video::LMT_ERROR);
	}

	m_shaderProgram = glCreateProgram();
	glAttachShader(m_shaderProgram, vertexShader);
	glAttachShader(m_shaderProgram, fragmentShader);
	glLinkProgram(m_shaderProgram);

	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_shaderProgram, MAX_MESSAGE_SIZE, NULL, infoLog);
		video->Log("glLinkProgram: " + std::string(infoLog), Video::LMT_ERROR);
	}
	
	glDetachShader(m_shaderProgram, vertexShader);
	glDetachShader(m_shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GLint GLShader::FindUniformLocation(const std::string& name, const bool isTexture)
{
	std::map<std::string, GLint>::iterator iter = m_parameters.find(name);
	if (iter != m_parameters.end())
	{
		return iter->second;
	}
	else
	{
		const GLint location = glGetUniformLocation(m_shaderProgram, name.c_str());
		if (location >= 0)
		{
			if (isTexture)
			{
				m_textureParamsIndices.insert(std::pair<std::string, GLint>(name, m_textureCount++));
			}
			m_parameters.insert(std::pair<std::string, GLint>(name, location));
		}
		return location;
	}
}

GLuint GLShader::GetShaderProgram() const
{
	return m_shaderProgram;
}

void GLShader::SetParameter(const std::string& name, const float v)
{
	const GLint location = FindUniformLocation(name, false /*isTexture*/);
	glUniform1f(location, v);
}

void GLShader::SetParameter(const std::string& name, const math::Vector2& v)
{
	const GLint location = FindUniformLocation(name, false /*isTexture*/);
	glUniform2f(location, v.x, v.y);
}

void GLShader::SetParameter(const std::string& name, const math::Vector3& v)
{
	const GLint location = FindUniformLocation(name, false /*isTexture*/);
	glUniform3f(location, v.x, v.y, v.z);
}

void GLShader::SetParameter(const std::string& name, const math::Vector4& v)
{
	const GLint location = FindUniformLocation(name, false /*isTexture*/);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void GLShader::SetParameter(const std::string& name, TexturePtr texture)
{
	const GLint location = FindUniformLocation(name, true /*isTexture*/);
	const GLint texParamIndex = m_textureParamsIndices[name];
	glUniform1i(location, texParamIndex);
	
	GLenum textureEnum = 0;
	switch (texParamIndex)
	{
		case 0:  textureEnum = GL_TEXTURE0; break;
		case 1:  textureEnum = GL_TEXTURE1; break;
		case 2:  textureEnum = GL_TEXTURE2; break;
		case 3:  textureEnum = GL_TEXTURE3; break;
		case 4:  textureEnum = GL_TEXTURE4; break;
		case 5:  textureEnum = GL_TEXTURE5; break;
		case 6:  textureEnum = GL_TEXTURE6; break;
		case 7:  textureEnum = GL_TEXTURE7; break;
		case 8:  textureEnum = GL_TEXTURE8; break;
		case 9:  textureEnum = GL_TEXTURE9; break;
		case 10: textureEnum = GL_TEXTURE10; break;
		case 11: textureEnum = GL_TEXTURE11; break;
		case 12: textureEnum = GL_TEXTURE12; break;
		case 13: textureEnum = GL_TEXTURE13; break;
		case 14: textureEnum = GL_TEXTURE14; break;
		case 15: textureEnum = GL_TEXTURE15; break;
		case 16: textureEnum = GL_TEXTURE16; break;
		case 17: textureEnum = GL_TEXTURE17; break;
		case 18: textureEnum = GL_TEXTURE18; break;
		case 19: textureEnum = GL_TEXTURE19; break;
		case 20: textureEnum = GL_TEXTURE20; break;
		case 21: textureEnum = GL_TEXTURE21; break;
		case 22: textureEnum = GL_TEXTURE22; break;
		case 23: textureEnum = GL_TEXTURE23; break;
		case 24: textureEnum = GL_TEXTURE24; break;
		case 25: textureEnum = GL_TEXTURE25; break;
		case 26: textureEnum = GL_TEXTURE26; break;
		case 27: textureEnum = GL_TEXTURE27; break;
		case 28: textureEnum = GL_TEXTURE28; break;
		case 29: textureEnum = GL_TEXTURE29; break;
		case 30: textureEnum = GL_TEXTURE30; break;
		case 31: textureEnum = GL_TEXTURE31; break;
	}

	glActiveTexture(textureEnum);
	
	GLTexture* texturePtr = (GLTexture*)texture.get();
	glBindTexture(GL_TEXTURE_2D, texturePtr->GetTexture());
}

} // namespace sprite
