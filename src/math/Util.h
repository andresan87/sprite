#ifndef SPRITE_MATH_UTIL_H_
#define SPRITE_MATH_UTIL_H_

#include <cstdint>

namespace sprite {
namespace math {

class Util
{
public:
	static const float PI;

	static bool IsPowerOfTwo(const uint64_t n);
	static double FindNextPowerOfTwoValue(const double n);
	static float RadianToDegree(const float angle);
	static float DegreeToRadian(const float angle);

	template <class T>
	static inline T Max(const T &a, const T &b)
	{
		return (a > b) ? a : b;
	}

	template <class T>
	static inline T Min(const T &a, const T &b)
	{
		return (a < b) ? a : b;
	}

	template <class T>
	static inline T Abs(const T &n)
	{
		return (n < 0) ? -n : n;
	}

	template <class T>
	static inline T Clamp(const T &n, const T &min, const T &max)
	{
		return (n < min) ? min : (n > max) ? max : n;
	}

	template <class T>
	static inline T Sign(const T &n)
	{
		return (n < static_cast<T>(0)) ? static_cast<T>(-1) : (n > static_cast<T>(0)) ? static_cast<T>(1) : static_cast<T>(0);
	}
};

} // namespace math
} // namespace sprite

#endif
