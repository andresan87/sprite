#ifndef SPRITE_PLATFORM_TEXTURE_H_
#define SPRITE_PLATFORM_TEXTURE_H_

#include "Video.h"

#include "../platform/FileManager.h"

#include "../math/Vector2.h"

namespace sprite {

class Texture;

typedef std::shared_ptr<Texture> TexturePtr;

class Texture
{
public:
	static TexturePtr Create(
		const VideoPtr& video,
		const FileManagerPtr fileManager,
		const std::string& fileName);
	
	virtual math::Vector2 GetResolution() const = 0;
};

} // namespace sprite

#endif
