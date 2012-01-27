#ifndef MATH_H
#define MATH_H

#include <cmath>

static const double PI = 4.0 * std::atan(1.0);

double degToRad(double degrees)
{
	return degrees * PI / 180.0;
}

double radToDeg(double radians)
{
	return radians * 180.0 / PI;
}

#endif // MATH_H
