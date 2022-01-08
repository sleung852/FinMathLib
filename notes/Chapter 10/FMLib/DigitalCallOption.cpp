#include "DigitalCallOption.h"

#include "matlib.h"


DigitalCallOption::DigitalCallOption() :
  strike(0.0),
  maturity(0.0) {
}

double DigitalCallOption::payoff( double stockAtMaturity ) const {
    if (stockAtMaturity>strike) {
        return 1.0;
    } else {
        return 0.0;
    }
}

// double DigitalCallOption::price( 
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
//     return S*normcdf(d1) - exp(-r*T)*K*normcdf(d2);
// }

double DigitalCallOption::getMaturity() const {
    return maturity;
}

//////////////////////////
//
//  Test the call option class
//  
//
//////////////////////////

static void testPayoff() {
    DigitalCallOption digitalCallOption;
    digitalCallOption.strike = 105.0;
    digitalCallOption.maturity = 2.0;
    ASSERT_APPROX_EQUAL( digitalCallOption.payoff(110.0), 1.0, 0.001);
    ASSERT_APPROX_EQUAL( digitalCallOption.payoff(100.0), 0.0, 0.001);
}

// static void testDigitalCallOptionPrice() {
//     DigitalCallOption digitalCallOption;
//     digitalCallOption.strike = 105.0;
//     digitalCallOption.maturity = 2.0;
    
//     BlackScholesModel bsm;
//     bsm.date = 1.0;
//     bsm.volatility = 0.1;
//     bsm.riskFreeRate = 0.05;
//     bsm.stockPrice = 100.0;

//     double price = digitalCallOption.price( bsm );
//     ASSERT_APPROX_EQUAL( price, 4.046, 0.01);
// }

void testDigitalCallOption() {
    TEST ( testPayoff );
    // TEST( testDigitalCallOptionPrice );
}
