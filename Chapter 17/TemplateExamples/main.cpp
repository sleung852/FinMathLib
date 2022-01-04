#include "stdafx.h"
#include "SimpleVector.h"
#include "minmax.h"
#include "BlackScholesModel.h"
#include "CallOption.h"
#include "MonteCarloPricer.h"
#include "testing.h"
#include "ComplexNumber.h"

using namespace std;

void testMonteCarloPricer() {
	CallOption c;
	c.strike = 110;
	c.maturity = 1;
	BlackScholesModel model;
	model.stockPrice = 100;
	model.drift = 0;
	model.riskFreeRate = 0.1;
	model.volatility = 0.2;
	model.date = 0;

	double price = monteCarloPrice(c, model);
	ASSERT_APPROX_EQUAL(price, c.price(model), 0.1);
}

void testMax() {
	ASSERT( findMax(3, 1)==3); // ints
	ASSERT( findMax(2.0, 3.0) == 3.0); // doubles
	ASSERT( findMax( string("ant"),
			string("zoo")) == string("zoo"));
}



void testSimpleVector() {
	SimpleVector<double> v1(3);
	v1.set(1, 2.0);
	ASSERT(v1.get(1) == 2.0);

	SimpleVector<int> v2(3);
	v2.set(1, 2);
	ASSERT(v2.get(1) == 2);

	SimpleVector<string> v3(3);
	v3.set(1, "Test string");
	ASSERT(v3.get(1) == "Test string");

}

void testArray() {
	array<int, 3> a;
	a[2] = 1;
	ASSERT(a[2] == 1);
}





int main() {
	testBlackScholesModel();
	TEST(testMonteCarloPricer);
	TEST(testMax);
	TEST(testSimpleVector);
	TEST(testArray);
	TEST(testComplexNumber);
	return 0;
}