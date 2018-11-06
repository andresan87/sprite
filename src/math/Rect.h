#ifndef SPRITE_MATH_Rect_H_
#define SPRITE_MATH_Rect_H_

#include "Vector2.h"

namespace sprite {
namespace math {

struct Rect
{
	Rect();
	Rect(const Vector2& p, const Vector2& s);
	Vector2 pos;
	Vector2 size;
};

} // namespace math

} // namespace sprite

#endif
