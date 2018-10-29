#include "GLShader.h"

#define MAX_MESSAGE_SIZE 1024

namespace sprite {

ShaderPtr Shader::Create(
	const VideoPtr& video,
	const std::string& vertexShaderSource,
	const std::string& fragmentShaderSource)
{
	std::shared_ptr<GLShader> r = std::make_shared<GLShader>(video, vertexShaderSource, fragmentShaderSource);
	return r;
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

GLuint GLShader::GetShaderProgram() const
{
	return m_shaderProgram;
}

} // namespace sprite
