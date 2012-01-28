/**
 * \file Math.h
 * \brief Contains useful math functions and constants.
 */
#ifndef MATH_H
#define MATH_H

#include <cmath>

static const double PI = 4.0 * std::atan(1.0); /**< Pi. */

/**
 * Convert degrees to radians.
 * 
 * \param degrees the angle (in degrees).
 * \return the angle (in radians).
 */
double degToRad(double degrees)
{
	return degrees * PI / 180.0;
}

/**
 * Convert radians to degrees.
 * 
 * \param radians the angle (in radians).
 * \return the angle (in degrees).
 */
double radToDeg(double radians)
{
	return radians * 180.0 / PI;
}

#endif // MATH_H
