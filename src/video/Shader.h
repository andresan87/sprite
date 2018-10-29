#ifndef SPRITE_PLATFORM_SHADER_H_
#define SPRITE_PLATFORM_SHADER_H_

#include "Video.h"

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
};

} // namespace sprite

#endif
