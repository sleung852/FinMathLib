#pragma once

#include<vector>

const double PI = 3.1415926535897932384626433832795028842;

class Circle {
public:
    explicit Circle(double radius);
    double radius;
    double area();
    double circumference();
};

class CartesianPoint {
public:
    CartesianPoint(double x, double y);
    CartesianPoint();
    double x;
    double y;
    double distanceTo(const CartesianPoint& other) const;
};

class PolarPoint {
public:
    PolarPoint(double r, double theta);
    PolarPoint();
    double r;
    double theta;
};

// 8.8.2

class Polynomial {
public:
    // constructors
    Polynomial();
    Polynomial(std::vector<double> coefficients);
    explicit Polynomial(double c);

    double evaluate(double x) const;
    void add(const Polynomial& other);

// private:
    std::vector<double> coefficients;

};


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
PolarPoint cartesianToPolar( const CartesianPoint& );

/**
 *  Converts polar coordinates to cartesian. Note, this changes x and y.
 */
CartesianPoint polarToCartesian( const PolarPoint& );

/**
 *  Compute the perimeter of a triangle
 */
double perimeter( const CartesianPoint& pointA, const CartesianPoint& pointB, const CartesianPoint& pointC );


/**
 *  Test suite
 */
void testGeometry();