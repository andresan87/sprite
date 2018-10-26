#ifndef SPRITE_MATH_VECTOR4_H_
#define SPRITE_MATH_VECTOR4_H_

#include <cstdint>

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
	
	static uint32_t ARGB(const char a, const char r, const char g, const char b);

	uint32_t ToARGBColor() const;
};

} // namespace math

typedef math::Vector4 Color;

} // namespace sprite

#endif
