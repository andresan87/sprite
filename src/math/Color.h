#ifndef SPRITE_COLOR_H_
#define SPRITE_COLOR_H_

#include "Vector4.h"

#include <cstdint>

namespace sprite {

struct Color : public math::Vector4
{
	static uint32_t ARGB(const char a, const char r, const char g, const char b);

	Color();
	Color(const Color& v);
	Color(const float fr, const float fg, const float fb, const float fa);
	Color(const float rgba);
	Color(const uint32_t color);

	uint32_t To32BitARGB() const;
	
	float GetA() const;
	float GetR() const;
	float GetG() const;
	float GetB() const;
};

} // namespace sprite

#endif
