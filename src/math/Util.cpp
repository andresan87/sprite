#include "Util.h"

#include <math.h>

namespace sprite {
namespace math {

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

} // namespace math
} // namespace sprite
