#include "Util.h"

#include <math.h>

namespace sprite {
namespace math {

const float Util::PI = 3.141592654f;

bool Util::IsPowerOfTwo(const uint64_t n)
{
	return (n != 0) && ((n & (n - 1)) == 0);
}

double Util::FindNextPowerOfTwoValue(const double n)
{
	unsigned int x = 1;
	double r;
	while ((r = pow(2, x++)) < n);
	return r;
}

float Util::RadianToDegree(const float angle)
{
	return (angle / (PI * 2)) * 360.0f;
}

float Util::DegreeToRadian(const float angle)
{
	return angle * (PI / 180.0f);
}

} // namespace math
} // namespace sprite
