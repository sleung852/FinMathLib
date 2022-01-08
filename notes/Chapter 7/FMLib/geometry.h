#pragma once
#include "stdafx.h"

const double PI = 3.1415926535897932384626433832795028842;

/**
 *   Computes the area of a circle
 */
double areaOfCircle(double r);

/**
 *  Computes the circumference of a circle
 */
double circumferenceOfCircle(double r);

/**
 *   Converts Cartesian coordinates to polar coordinates. Note this
 *   changes r and theta.
 */
void cartesianToPolar( double x, double y, double& r, double& theta );

/**
 *  Converts polar coordinates to cartesian. Note, this changes x and y.
 */
void polarToCartesian( double r, double theta, double& x, double& y );

/**
 *  Solves Quandratic Equation. Note, this changes root1 and root2.
 */
int solveQuadratic( double a, double b, double c, double& root1, double& root2 );

/**
 *  Solves Quandratic Equation, returns roots as std::vector
 */
std::vector<double> solveQuadraticAlt( double a, double b, double c);

/**
 *  Test suite
 */
void testGeometry();