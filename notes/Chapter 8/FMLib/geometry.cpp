#include "geometry.h"
#include "stdafx.h"
#include "testing.h"

using namespace std;

Circle::Circle(double r) :
	radius(r) {}

/**
 *   Computes the area of a circle
 */
double Circle::area() {
	return PI*radius*radius;
}

/**
 *  Computes the circumference of a circle
 */
double Circle::circumference() {
	return 2*PI*radius;
}

CartesianPoint::CartesianPoint(double x_in, double y_in) :
	x(x_in), y(y_in) {}

CartesianPoint::CartesianPoint() :
	x(0), y(0) {}

PolarPoint::PolarPoint(double r_in, double theta_in) :
	r(r_in), theta(theta_in) {}

PolarPoint::PolarPoint():
	r(0), theta(0) {}

/**
 *  Converts polar coordinates to cartesian. Note, this changes x and y.
 */
CartesianPoint polarToCartesian(const PolarPoint& p){
    CartesianPoint c;
	c.x = p.r*cos( p.theta );
	c.y = p.r*sin( p.theta );
    return c;
}

/**
 *   Converts Cartesian coordinates to polar coordinates. Note this
 *   changes r and theta.
 */
PolarPoint cartesianToPolar( const CartesianPoint& c) {
    PolarPoint p;
	// Not as easy as it looks to do this
	p.r = sqrt( c.x*c.x + c.y*c.y);
	if (c.y==0.0) {
		if (c.x>=0.0) {
			p.theta = 0.0;
		} else if (c.x<0.0) {
			p.theta = -PI;
		}
	} else {
		p.theta = acos( c.x/p.r);
		if (c.y<0) {
			p.theta = -p.theta;
		}
	}
    return p;
}

// 8.6.3
double CartesianPoint::distanceTo(const CartesianPoint& other) const {
	return sqrt(pow(x-other.x, 2.0) + pow(y-other.y, 2.0));
}

// 8.6.4
double perimeter( const CartesianPoint& pointA, const CartesianPoint& pointB, const CartesianPoint& pointC ) {
	return pointA.distanceTo(pointB) + pointB.distanceTo(pointC) + pointC.distanceTo(pointA);
}

// 8.8.2
Polynomial::Polynomial() :
	coefficients(0.0) {}

Polynomial::Polynomial(std::vector<double> coefficients_in) :
	coefficients(coefficients_in) {}

Polynomial::Polynomial(double c) :
	coefficients({c, 0.0}) {}
	
double Polynomial::evaluate(double x) const {
	double sum = coefficients.at(0);
	if (coefficients.size() == 1) return sum;
	for (int i=1; i< coefficients.size(); i++) {
		sum += coefficients.at(i) * pow(x,i);
	}
	sum += pow(x,coefficients.size());
	return sum;
}

void Polynomial::add(const Polynomial& other){
	if (other.coefficients.size() > coefficients.size()) {
		for (int i=other.coefficients.size()-coefficients.size();
			i<other.coefficients.size(); i++) {
				coefficients.push_back(other.coefficients.at(i));
			}
	}
	for (int i=0; i<coefficients.size(); i++) {
		if (i < other.coefficients.size()) {
			coefficients[i] += other.coefficients.at(i);
		}
	}
}

/////////////////////////////////////////////////
//
//  Geometry tests
//
/////////////////////////////////////////////////

static void testUsage() {
    CartesianPoint p;
    p.x = 100;
    p.y = 150;
    cout << "Coordinates (";
    cout << p.x ;
    cout << ", ";
    cout << p.y ;
    cout << ")\n";

    p.x *= 2;
    p.y *= 2;
    cout << "Rescaled cordinates (";
    cout << p.x ;
    cout << ", ";
    cout << p.y ;
    cout << ")\n";
}

static void testAreaOfCircle() {
    Circle c(4);
	ASSERT_APPROX_EQUAL( c.area(), 16*PI, 0.01 );
}

static void testCircumferenceOfCircle() {
    Circle c(2);
	ASSERT_APPROX_EQUAL(c.circumference(),4*PI,0.01);
}

static void testPolarToCartesian() {
    PolarPoint p(2.0, PI/2);
	CartesianPoint c = polarToCartesian( p );
	ASSERT_APPROX_EQUAL( c.x,0.0,0.001 );
	ASSERT_APPROX_EQUAL( c.y,2.0,0.001 );
}

static void testCartesianToPolar() {
	// the logic of cartesian to polar is quite complex so we have more tests
	vector<double> angles;
	angles.push_back( 0.0 );
	angles.push_back( PI/4 );
	angles.push_back( PI/2 );
	angles.push_back( 7*PI/8 );
	angles.push_back( PI);
	angles.push_back( -PI/4 );
	angles.push_back( -PI/2 );
	angles.push_back( -7*PI/8 );

	int nAngles = angles.size();
	for (int i=0; i<nAngles; i++) {
        PolarPoint p;
		p.r = 2.0;
		p.theta =angles[i];
		CartesianPoint c =polarToCartesian( p);
		PolarPoint p2;
		p2 = cartesianToPolar( c );
		ASSERT_APPROX_EQUAL( p.r,p2.r,0.001 );
		ASSERT_APPROX_EQUAL( p.theta,p2.theta,0.001 );
	}
}

static void testDistanceTo() {
	CartesianPoint p1;
	p1.x = 0;
	p1.y = 0;
	CartesianPoint p2;
	p2.x = 3;
	p2.y = 4;
	double d = p1.distanceTo(p2);
	ASSERT_APPROX_EQUAL(d, 5, 0.01);
}

static void testPerimeter() {
	CartesianPoint p1;
	p1.x = 0;
	p1.y = 0;
	CartesianPoint p2;
	p2.x = 3;
	p2.y = 0;
	CartesianPoint p3;
	p3.x = 3;
	p3.y = 4;
	double p = perimeter(p1, p2, p3);
	ASSERT_APPROX_EQUAL(p, 3+4+5, 0.01);
}

static void testPolynomial() {
	// test constructors
	Polynomial p1;
	vector<double> test_v({1,2,3,4,5});
	Polynomial p2(test_v);
	Polynomial p3(7.1);
	Polynomial p4(vector<double>({3.0,2.0,1.0}));
	ASSERT_APPROX_EQUAL(p3.coefficients[0], 7.1, 0.01);
	ASSERT_APPROX_EQUAL(p3.coefficients[1], 0, 0.01);
	// test evaluate
	ASSERT_APPROX_EQUAL(p2.evaluate(1.0), 16, 0.01);
	ASSERT_APPROX_EQUAL(p4.evaluate(2.0), 3.0+4.0+4.0+8.0, 0.01);
	// test add
	p2.add(p4);
	ASSERT_APPROX_EQUAL(p2.evaluate(1.0), 4+4+4+4+5+1, 0.01);
}

void testGeometry() {
    TEST (testUsage );
	TEST( testAreaOfCircle );
	TEST( testCircumferenceOfCircle );
	TEST( testPolarToCartesian );
	TEST( testCartesianToPolar );
	TEST( testDistanceTo );
	TEST( testPerimeter );
	TEST( testPolynomial );
}