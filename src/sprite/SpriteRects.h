#ifndef SPRITE_SPRITE_RECTS_H_
#define SPRITE_SPRITE_RECTS_H_

#include "../math/Rect.h"

#include <memory>
#include <vector>

namespace sprite {

class SpriteRects;

typedef std::shared_ptr<SpriteRects> SpriteRectsPtr;

class SpriteRects
{
	std::vector<math::Rect> m_rects;

public:
	SpriteRects();
	SpriteRects(const std::vector<math::Rect>& rects);

	void SetRects(const unsigned int columns, const unsigned int rows);
	void SetRects(const std::vector<math::Rect>& rects);

	math::Rect GetRect(const unsigned int r) const;

	unsigned int GetNumRects() const;
};

} // namespace sprite

#endif
