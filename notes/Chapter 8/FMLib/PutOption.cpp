#include "PutOption.h"
#include "matlib.h"

PutOption::PutOption() :
    strike(0.0), maturity(0.0) {}

PutOption::PutOption(double strike_in, double maturity_in) :
    strike(strike_in), maturity(maturity_in) {}

double PutOption::payoff( double stockAtMaturity ) const {
    if (stockAtMaturity < strike) return strike - stockAtMaturity;
    else return 0.0;
} 

double PutOption::price( const BlackScholesModel& bsm ) const {
    double T = maturity - bsm.date;
    double d1 = (log(bsm.stockPrice/strike) + (bsm.riskFreeRate + pow(bsm.volatility, 2) * bsm.date))/(bsm.volatility * sqrt(T));
    double d2 = d1 - bsm.volatility * sqrt(T);
    return strike * exp(-bsm.riskFreeRate*T) * normcdf(-d2) - bsm.stockPrice * normcdf(-d1);
}

/*
Test Put Options
*/ 
static void testPutOptionPrice() {
    PutOption putOption;
    putOption.strike = 105.0;
    putOption.maturity = 2.0;
    
    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double price = putOption.price( bsm );
    //https://billmei.github.io/SimpleBlackScholes/
    ASSERT_APPROX_EQUAL( price, 3.925, 0.01);
}

void testPutOption() {
    TEST( testPutOptionPrice );
}