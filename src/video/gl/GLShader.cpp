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
	m_program(0)
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
		video->Log("glCompileShader vertex: " + std::string(infoLog), Logger::LMT_ERROR);
	}

	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCstr, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, MAX_MESSAGE_SIZE, NULL, infoLog);
		video->Log("glCompileShader fragment: " + std::string(infoLog), Logger::LMT_ERROR);
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_program, MAX_MESSAGE_SIZE, NULL, infoLog);
		video->Log("glLinkProgram: " + std::string(infoLog), Logger::LMT_ERROR);
	}
	
	glDetachShader(m_program, vertexShader);
	glDetachShader(m_program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_vPositionLocation = glGetAttribLocation(m_program, "vPosition");
	m_vTexCoordLocation = glGetAttribLocation(m_program, "vTexCoord");
	m_vNormalLocation = glGetAttribLocation(m_program, "vNormal");
}

GLint GLShader::GetVPositionLocation() const
{
	return m_vPositionLocation;
}

GLint GLShader::GetVTexCoordLocation() const
{
	return m_vTexCoordLocation;
}

GLint GLShader::GetVNormalLocation() const
{
	return m_vNormalLocation;
}

GLint GLShader::FindUniformLocation(const std::string& name)
{
	tsl::hopscotch_map<std::string, GLint>::iterator iter = m_parameters.find(name);
	if (iter != m_parameters.end())
	{
		return iter->second;
	}
	else
	{
		const GLint location = glGetUniformLocation(m_program, name.c_str());
		if (location >= 0)
		{
			m_parameters.insert(std::pair<std::string, GLint>(name, location));
		}
		return location;
	}
}

void GLShader::SetShader()
{
	glUseProgram(m_program);
}

void GLShader::SetParameter(const std::string& name, const float v)
{
	const GLint location = FindUniformLocation(name);
	glUniform1f(location, v);
}

void GLShader::SetParameter(const std::string& name, const math::Vector2& v)
{
	const GLint location = FindUniformLocation(name);
	glUniform2f(location, v.x, v.y);
}

void GLShader::SetParameter(const std::string& name, const math::Vector3& v)
{
	const GLint location = FindUniformLocation(name);
	glUniform3f(location, v.x, v.y, v.z);
}

void GLShader::SetParameter(const std::string& name, const math::Vector4& v)
{
	const GLint location = FindUniformLocation(name);
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

void GLShader::SetParameter(const std::string& name, TexturePtr texture, const unsigned int index)
{
	const GLint location = FindUniformLocation(name);
	glUniform1i(location, index);
	glActiveTexture(GL_TEXTURE0 + index);

	GLTexture* texturePtr = (GLTexture*)texture.get();
	glBindTexture(GL_TEXTURE_2D, texturePtr->GetTexture());
}

} // namespace sprite
