#ifndef SPRITE_PLATFORM_GLTEXTURE_H_
#define SPRITE_PLATFORM_GLTEXTURE_H_

#include "../Texture.h"

#include "GLInclude.h"

namespace sprite {

class GLTexture : public Texture
{
	GLuint m_texture;
	
	math::Vector2 m_resolution;

public:
	GLTexture(
		const VideoPtr& video,
		const FileManagerPtr fileManager,
		const std::string& fileName);
	
	~GLTexture();

	math::Vector2 GetResolution() const;

	GLuint GetTexture() const;
};

} // namespace sprite

#endif
