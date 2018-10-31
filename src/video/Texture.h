#ifndef SPRITE_PLATFORM_TEXTURE_H_
#define SPRITE_PLATFORM_TEXTURE_H_

#include "Video.h"

#include "../platform/FileManager.h"

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
};

} // namespace sprite

#endif
