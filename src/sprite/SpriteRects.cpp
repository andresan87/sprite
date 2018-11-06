#include "SpriteRects.h"

namespace sprite {

SpriteRects::SpriteRects()
{
}

SpriteRects::SpriteRects(const std::vector<math::Rect>& rects)
{
	SetRects(rects);
}

void SpriteRects::SetRects(const unsigned int columns, const unsigned int rows)
{
	using namespace math;

	const float strideX = 1.0f / (float)columns;
	const float strideY = 1.0f / (float)rows;

	m_rects.clear();

	for (float y = 0.0f; y < (float)rows; y++)
	{
		for (float x = 0.0f; x < (float)columns; x++)
		{
			m_rects.push_back(Rect(Vector2(x * strideX, y * strideY), Vector2(strideX, strideY)));
		}
	}
}

void SpriteRects::SetRects(const std::vector<math::Rect>& rects)
{
	m_rects = rects;
}

math::Rect SpriteRects::GetRect(const unsigned int r) const
{
	if (m_rects.size() > 0)
		return m_rects[r % m_rects.size()];
	else
		return math::Rect();
}

unsigned int SpriteRects::GetNumRects() const
{
	return (unsigned int)m_rects.size();
}

} // namespace sprite
