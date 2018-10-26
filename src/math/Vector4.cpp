#include "Vector4.h"

#include <math.h>

namespace sprite {
namespace math {

Vector4::Vector4()
{
	x = y = z = w = 0.0f;
}

Vector4::Vector4(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Vector4::Vector4(const float fx, const float fy, const float fz, const float fw)
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}

Vector4::Vector4(float xyzw)
{
	x = y = z = w = xyzw;
}

float Vector4::Length() const
{
	return sqrtf(SquaredLength());
}

float Vector4::SquaredLength() const
{
	return ((x * x) + (y * y) + (z * z) + (w * w));
}

Vector4 Vector4::operator * (const float v) const
{
	return Vector4(x * v, y * v, z * v, w * v);
}

Vector4 Vector4::operator * (const Vector4& v) const
{
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

Vector4 Vector4::operator / (const float v) const
{
	return Vector4(x / v, y / v, z / v, w / v);
}

Vector4 Vector4::operator / (const Vector4& v) const
{
	return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

Vector4 Vector4::operator - (const float v) const
{
	return Vector4(x - v, y - v, z - v, w - v);
}

Vector4 Vector4::operator - (const Vector4& v) const
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector4 Vector4::operator + (const float v) const
{
	return Vector4(x + v, y + v, z + v, w + v);
}

Vector4 Vector4::operator + (const Vector4& v) const
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

bool Vector4::operator == (const Vector4& v) const
{
	return (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool Vector4::operator != (const Vector4& v) const
{
	return !(*this == v);
}

Vector4& Vector4::operator += (const Vector4& v)
{
	*this = Vector4(x, y, z, w) + v;
	return *this;
}

Vector4& Vector4::operator -= (const Vector4& v)
{
	*this = Vector4(x, y, z, w) - v;
	return *this;
}

Vector4& Vector4::operator *= (const float f)
{
	*this = Vector4(x, y, z, w) * f;
	return *this;
}

Vector4& Vector4::operator /= (const float f)
{
	*this = Vector4(x, y, z, w) / f;
	return *this;
}

uint32_t Vector4::ARGB(const char a, const char r, const char g, const char b)
{
	return
	(
		(((a) & 0xff) << 24) |
		(((r) & 0xff) << 16) |
		(((g) & 0xff) <<  8) |
		(((b) & 0xff) <<  0)
	);
}

uint32_t Vector4::ToARGBColor() const
{
	return ARGB(char(w * 255.0f), char(x * 255.0f), char(y * 255.0f), char(z * 255.0f));
}

} // namespace math
} // namespace sprite
