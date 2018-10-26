#include "Vector3.h"

#include <math.h>

namespace sprite {
namespace math {

Vector3::Vector3()
{
	x = y = z = 0.0f;
}

Vector3::Vector3(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3::Vector3(const float fx, const float fy, const float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

Vector3::Vector3(float xyz)
{
	x = y = z = xyz;
}

float Vector3::Length() const
{
	return sqrtf(SquaredLength());
}

float Vector3::SquaredLength() const
{
	return ((x * x) + (y * y) + (z * z));
}

Vector3 Vector3::operator * (const float v) const
{
	return Vector3(x * v, y * v, z * v);
}

Vector3 Vector3::operator * (const Vector3& v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator / (const float v) const
{
	return Vector3(x / v, y / v, z / v);
}

Vector3 Vector3::operator / (const Vector3& v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator - (const float v) const
{
	return Vector3(x - v, y - v, z - v);
}

Vector3 Vector3::operator - (const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator + (const float v) const
{
	return Vector3(x + v, y + v, z + v);
}

Vector3 Vector3::operator + (const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

bool Vector3::operator == (const Vector3& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

bool Vector3::operator != (const Vector3& v) const
{
	return !(*this == v);
}

Vector3& Vector3::operator += (const Vector3& v)
{
	*this = Vector3(x, y, z) + v;
	return *this;
}

Vector3& Vector3::operator -= (const Vector3& v)
{
	*this = Vector3(x, y, z) - v;
	return *this;
}

Vector3& Vector3::operator *= (float f)
{
	*this = Vector3(x, y, z) * f;
	return *this;
}

Vector3& Vector3::operator /= (float f)
{
	*this = Vector3(x, y, z) / f;
	return *this;
}

} // namespace math
} // namespace sprite
