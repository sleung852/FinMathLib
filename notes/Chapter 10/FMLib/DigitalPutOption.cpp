#include "DigitalPutOption.h"

#include "matlib.h"


DigitalPutOption::DigitalPutOption() :
  strike(0.0),
  maturity(0.0) {
}

double DigitalPutOption::payoff( double stockAtMaturity ) const {
    if (stockAtMaturity<strike) {
        return 1.0;
    } else {
        return 0.0;
    }
}

// double DigitalPutOption::price(
//         const BlackScholesModel& bsm ) const {
//     double S = bsm.stockPrice;
//     double K = strike;
//     double sigma = bsm.volatility;
//     double r = bsm.riskFreeRate;
//     double T = maturity - bsm.date;

//     double numerator = log( S/K ) + ( r + sigma*sigma*0.5)*T;
//     double denominator = sigma * sqrt(T );
//     double d1 = numerator/denominator;
//     double d2 = d1 - denominator;
//     return -S*normcdf(-d1) + exp(-r*T)*K*normcdf(-d2);
// }


double DigitalPutOption::getMaturity() const {
    return maturity;
}


//////////////////////////
//
//  Test the call option class
//
//
//////////////////////////

static void testPayoff() {
    DigitalPutOption digitalPutOption;
    digitalPutOption.strike = 105.0;
    digitalPutOption.maturity = 2.0;
    ASSERT_APPROX_EQUAL( digitalPutOption.payoff(110.0), 0.0, 0.001);
    ASSERT_APPROX_EQUAL( digitalPutOption.payoff(100.0), 1.0, 0.001);
}

// static void testDigitalPutOptionPrice() {
//     DigitalPutOption digitalPutOption;
//     digitalPutOption.strike = 105.0;
//     digitalPutOption.maturity = 2.0;

//     BlackScholesModel bsm;
//     bsm.date = 1.0;
//     bsm.volatility = 0.1;
//     bsm.riskFreeRate = 0.05;
//     bsm.stockPrice = 100.0;

//     double price = digitalPutOption.price( bsm );
//     ASSERT_APPROX_EQUAL( price, 3.925, 0.01);
// }

void testDigitalPutOption() {
    // TEST( testDigitalPutOptionPrice );
    TEST( testPayoff );
}
