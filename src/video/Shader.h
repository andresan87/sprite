#ifndef SPRITE_PLATFORM_SHADER_H_
#define SPRITE_PLATFORM_SHADER_H_

#include "Video.h"

#include "../math/Vector2.h"
#include "../math/Vector3.h"
#include "../math/Vector4.h"

#include <memory>
#include <string>

namespace sprite {

class Shader;

typedef std::shared_ptr<Shader> ShaderPtr;

class Shader
{
public:
	static ShaderPtr Create(
		const VideoPtr& video,
		const std::string& vertexShaderSource,
		const std::string& fragmentShaderSource);

	virtual void SetParameter(const std::string& name, const float v) = 0;
	virtual void SetParameter(const std::string& name, const math::Vector2& v) = 0;
	virtual void SetParameter(const std::string& name, const math::Vector3& v) = 0;
	virtual void SetParameter(const std::string& name, const math::Vector4& v) = 0;
};

} // namespace sprite

#endif
