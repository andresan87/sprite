#include "GLShader.h"

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
	const std::string& fragmentShaderSource)
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

GLint GLShader::FindUniformLocation(const std::string& name)
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

} // namespace sprite
