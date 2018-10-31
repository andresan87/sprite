#ifndef SPRITE_MATH_UTIL_H_
#define SPRITE_MATH_UTIL_H_

#include <cstdint>

namespace sprite {
namespace math {

class Util
{
public:
	static bool IsPowerOfTwo(const uint64_t n);
	static double FindNextPowerOfTwoValue(const double n);
};

} // namespace math
} // namespace sprite

#endif
