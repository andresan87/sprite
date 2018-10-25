#ifndef SPRITE_MATH_VECTOR2_H_
#define SPRITE_MATH_VECTOR2_H_

namespace sprite {
namespace math {

struct PODVector2
{
	float x, y;
};

struct Vector2 : public PODVector2
{
	Vector2();
	Vector2(const Vector2& v2);
	Vector2(float fx, float fy);
	Vector2(float xy);
	float Length() const;
	float SquaredLength() const;
	Vector2 operator * (float v) const;
	Vector2 operator * (const Vector2& v) const;
	Vector2 operator / (float v) const;
	Vector2 operator / (const Vector2& v) const;
	Vector2 operator - (float v) const;
	Vector2 operator - (const Vector2& v) const;
	Vector2 operator + (float v) const;
	Vector2 operator + (const Vector2& v) const;
	bool operator == (const Vector2& v) const;
	bool operator != (const Vector2& v2) const;
	Vector2& operator += (const Vector2& v2);
	Vector2& operator -= (const Vector2& v2);
	Vector2& operator *= (float f);
	Vector2& operator /= (float f);
};


} // namespace math
} // namespace sprite

#endif
