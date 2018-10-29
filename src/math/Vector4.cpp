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

} // namespace math
} // namespace sprite
