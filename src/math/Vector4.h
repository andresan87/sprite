#ifndef SPRITE_MATH_VECTOR4_H_
#define SPRITE_MATH_VECTOR4_H_

#include "Vector2.h"

namespace sprite {
namespace math {

struct PODVector4
{
	float x, y, z, w;
};

struct Vector4 : public PODVector4
{
	Vector4();
	Vector4(const Vector4& v);
	Vector4(const float fx, const float fy, const float fz, const float fw);
	Vector4(const Vector2& a, const Vector2& b);
	Vector4(const float xyzw);
	float Length() const;
	float SquaredLength() const;
	Vector4 operator * (const float v) const;
	Vector4 operator * (const Vector4& v) const;
	Vector4 operator / (const float v) const;
	Vector4 operator / (const Vector4& v) const;
	Vector4 operator - (const float v) const;
	Vector4 operator - (const Vector4& v) const;
	Vector4 operator + (const float v) const;
	Vector4 operator + (const Vector4& v) const;
	bool operator == (const Vector4& v) const;
	bool operator != (const Vector4& v) const;
	Vector4& operator += (const Vector4& v);
	Vector4& operator -= (const Vector4& v);
	Vector4& operator *= (const float f);
	Vector4& operator /= (const float f);
};

} // namespace math

} // namespace sprite

#endif
