#ifndef SPRITE_PLATFORM_SHADER_H_
#define SPRITE_PLATFORM_SHADER_H_

#include "Video.h"
#include "Texture.h"

#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"

#include "../utilities/tsl/hopscotch_map.h"

#include <memory>
#include <string>

namespace sprite {

class Shader;

typedef std::shared_ptr<Shader> ShaderPtr;

class Shader
{
public:

	class ShaderParameter
	{
	public:
		virtual void SetParameter(const std::string& name, const ShaderPtr& shader) = 0;
	};
	
	class TextureShaderParameter : public ShaderParameter
	{
		TexturePtr m_texture;
		unsigned int m_index;
	public:
		TextureShaderParameter(const TexturePtr& texture, const unsigned int index);
		void SetParameter(const std::string& name, const ShaderPtr& shader);
	};

	class FloatShaderParameter : public ShaderParameter
	{
		float m_f;
	public:
		FloatShaderParameter(const float f);
		void SetParameter(const std::string& name, const ShaderPtr& shader);
	};

	class Vector2ShaderParameter : public ShaderParameter
	{
		math::Vector2 m_v;
	public:
		Vector2ShaderParameter(const math::Vector2& v);
		void SetParameter(const std::string& name, const ShaderPtr& shader);
	};

	class Vector3ShaderParameter : public ShaderParameter
	{
		math::Vector3 m_v;
	public:
		Vector3ShaderParameter(const math::Vector3& v);
		void SetParameter(const std::string& name, const ShaderPtr& shader);
	};

	class Vector4ShaderParameter : public ShaderParameter
	{
		math::Vector4 m_v;
	public:
		Vector4ShaderParameter(const math::Vector4& v);
		void SetParameter(const std::string& name, const ShaderPtr& shader);
	};

	static ShaderPtr Create(
		const VideoPtr& video,
		const std::string& vertexShaderSource,
		const std::string& fragmentShaderSource);

	virtual void SetShader() = 0;

	virtual void SetParameter(const std::string& name, const float v) = 0;
	virtual void SetParameter(const std::string& name, const math::Vector2& v) = 0;
	virtual void SetParameter(const std::string& name, const math::Vector3& v) = 0;
	virtual void SetParameter(const std::string& name, const math::Vector4& v) = 0;
	virtual void SetParameter(const std::string& name, TexturePtr texture, const unsigned int index) = 0;
	virtual void SetConstantArray(const std::string& name, unsigned int nElements, const math::Vector4* v) = 0;
};

typedef std::shared_ptr<Shader::ShaderParameter> ShaderParameterPtr;
typedef tsl::hopscotch_map<std::string, ShaderParameterPtr> ShaderParameters;
typedef std::shared_ptr<ShaderParameters> ShaderParametersPtr;

} // namespace sprite

#endif
