#include "Math.hpp"

#include <cmath>

namespace liq
{
	
	float64 log(float64 base, float64 x)
	{
		return std::log(x)/std::log(base);
	}
	
}