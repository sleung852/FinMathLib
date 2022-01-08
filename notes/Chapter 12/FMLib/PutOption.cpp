#include "PutOption.h"

#include "matlib.h"

double PutOption::payoff( double lastStockPrice) const {
    if (lastStockPrice<getStrike()) {
        return getStrike()-lastStockPrice;
    } else {
        return 0.0;
    }
}

double PutOption::price(
        const BlackScholesModel& bsm ) const {
    double S = bsm.stockPrice;
    double K = getStrike();
    double sigma = bsm.volatility;
    double r = bsm.riskFreeRate;
    double T = getMaturity() - bsm.date;

    double numerator = log( S/K ) + ( r + sigma*sigma*0.5)*T;
    double denominator = sigma * sqrt(T );
    double d1 = numerator/denominator;
    double d2 = d1 - denominator;
    return -S*normcdf(-d1) + exp(-r*T)*K*normcdf(-d2);
}



//////////////////////////
//
//  Test the call option class
//
//
//////////////////////////

static void testPayoff() {
    PutOption putOption;
    putOption.setStrike( 105.0) ;
    putOption.setMaturity( 2.0 );
    std::vector<double> d;
    d.push_back(110.0);
    ASSERT_APPROX_EQUAL( putOption.payoff(d), 0.0, 0.001);
    d[0]=100.0;
    ASSERT_APPROX_EQUAL( putOption.payoff(d), 5.0, 0.001);
}

static void testPutOptionPrice() {
    PutOption putOption;
    putOption.setStrike( 105.0 );
    putOption.setMaturity( 2.0 );

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double price = putOption.price( bsm );
    ASSERT_APPROX_EQUAL( price, 3.925, 0.01);
}

void testPutOption() {
    TEST( testPutOptionPrice );
    TEST( testPayoff );
}
