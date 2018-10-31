#ifndef SPRITE_PLATFORM_RENDER_TARGET_H_
#define SPRITE_PLATFORM_RENDER_TARGET_H_

#include "Texture.h"

namespace sprite {

class RenderTarget;

typedef std::shared_ptr<RenderTarget> RenderTargetPtr;

class RenderTarget : public Texture
{
public:
};

} // namespace sprite

#endif
