#ifndef SPRITE_MATH_VECTOR3_H_
#define SPRITE_MATH_VECTOR3_H_

#include "Vector2.h"

namespace sprite {
namespace math {

struct PODVector3
{
	float x, y, z;
};

struct Vector3 : public PODVector3
{
	Vector3();
	Vector3(const Vector3& v);
	Vector3(const Vector2& v, const float fz);
	Vector3(const float fx, const float fy, const float fz);
	Vector3(const float xyz);
	float Length() const;
	float SquaredLength() const;
	Vector3 operator * (const float v) const;
	Vector3 operator * (const Vector3& v) const;
	Vector3 operator / (const float v) const;
	Vector3 operator / (const Vector3& v) const;
	Vector3 operator - (const float v) const;
	Vector3 operator - (const Vector3& v) const;
	Vector3 operator + (const float v) const;
	Vector3 operator + (const Vector3& v) const;
	bool operator == (const Vector3& v) const;
	bool operator != (const Vector3& v) const;
	Vector3& operator += (const Vector3& v);
	Vector3& operator -= (const Vector3& v);
	Vector3& operator *= (const float f);
	Vector3& operator /= (const float f);
};

} // namespace math
} // namespace sprite

#endif
