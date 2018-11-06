#include "Rect.h"

namespace sprite {
namespace math {

Rect::Rect() :
	pos(0.0f),
	size(1.0f)
{
}

Rect::Rect(const Vector2& p, const Vector2& s) :
	pos(p),
	size(s)
{
}

} // namespace math

} // namespace sprite
