#include "Shader.h"

namespace sprite {

Shader::TextureShaderParameter::TextureShaderParameter(const TexturePtr& texture) :
	m_texture(texture)
{
}

void Shader::TextureShaderParameter::SetParameter(const std::string& name, const ShaderPtr& shader)
{
	shader->SetParameter(name, m_texture);
}

Shader::FloatShaderParameter::FloatShaderParameter(const float f) :
	m_f(f)
{
}

void Shader::FloatShaderParameter::SetParameter(const std::string& name, const ShaderPtr& shader)
{
	shader->SetParameter(name, (float)m_f);
}

Shader::Vector2ShaderParameter::Vector2ShaderParameter(const math::Vector2& v) :
	m_v(v)
{
}

void Shader::Vector2ShaderParameter::SetParameter(const std::string& name, const ShaderPtr& shader)
{
	shader->SetParameter(name, m_v);
}

Shader::Vector3ShaderParameter::Vector3ShaderParameter(const math::Vector3& v) :
	m_v(v)
{
}

void Shader::Vector3ShaderParameter::SetParameter(const std::string& name, const ShaderPtr& shader)
{
	shader->SetParameter(name, m_v);
}

Shader::Vector4ShaderParameter::Vector4ShaderParameter(const math::Vector4& v) :
	m_v(v)
{
}

void Shader::Vector4ShaderParameter::SetParameter(const std::string& name, const ShaderPtr& shader)
{
	shader->SetParameter(name, m_v);
}

} // namespace sprite
