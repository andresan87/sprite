#include "Color.h"

namespace sprite {

Color::Color() :
	math::Vector4(1.0f)
{
}

Color::Color(const Color& v) :
	math::Vector4(v)
{
}

Color::Color(const float fr, const float fg, const float fb, const float fa) :
	math::Vector4(fr, fg, fb, fa)
{
}

Color::Color(const uint32_t color)
{
	uint32_t a, r, g, b;
	a = (0xFF000000 & color) >> 24;
	r = (0x00FF0000 & color) >> 16;
	g = (0x0000FF00 & color) >> 8;
	b = (0x000000FF & color) >> 0;
	w = float(a) / 255.0f;
	x = float(r) / 255.0f;
	y = float(g) / 255.0f;
	z = float(b) / 255.0f;
}

uint32_t Color::ARGB(const char a, const char r, const char g, const char b)
{
	return
	(
		(((a) & 0xff) << 24) |
		(((r) & 0xff) << 16) |
		(((g) & 0xff) <<  8) |
		(((b) & 0xff) <<  0)
	);
}

uint32_t Color::To32BitARGB() const
{
	return ARGB(char(w * 255.0f), char(x * 255.0f), char(y * 255.0f), char(z * 255.0f));
}

float Color::GetA() const
{
	return w;
}

float Color::GetR() const
{
	return x;
}

float Color::GetG() const
{
	return y;
}

float Color::GetB() const
{
	return z;
}

} // namespace sprite
