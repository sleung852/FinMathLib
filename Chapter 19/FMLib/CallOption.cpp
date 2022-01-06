#include "CallOption.h"

#include "matlib.h"


Matrix CallOption::payoffAtMaturity( const Matrix& stockAtMaturity ) const {
    Matrix val = stockAtMaturity - getStrike();
    val.positivePart();
    return val;
}

double CallOption::price( 
        const MultiStockModel& msm ) const {
	BlackScholesModel bsm = msm.getBlackScholesModel(getStock());
    double S = bsm.stockPrice;
    double K = getStrike();
    double sigma = bsm.volatility;
    double r = bsm.riskFreeRate;
    double T = getMaturity() - bsm.date;

    double numerator = log( S/K ) + ( r + sigma*sigma*0.5)*T;
    double denominator = sigma * sqrt(T );
    double d1 = numerator/denominator;
    double d2 = d1 - denominator;
    return S*normcdf(d1) - exp(-r*T)*K*normcdf(d2);
}

//////////////////////////
//
//  Test the call option class
//  
//
//////////////////////////

static void testCallOptionPrice() {
    CallOption callOption;
    callOption.setStrike( 105.0 );
    callOption.setMaturity( 2.0 );
    
    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

	MultiStockModel msm(bsm);

    double price = callOption.price( msm );
    ASSERT_APPROX_EQUAL( price, 4.046, 0.01);
}

void testCallOption() {
    TEST( testCallOptionPrice );
}

// 19.4.4
double impliedVolatility(double S, double r, double K, double date,
    double maturity, double price, double a, double b, double threshold) {
    CallOption callOption;
    callOption.setStrike( K );
    callOption.setMaturity( maturity );
    
    BlackScholesModel bsm;
    bsm.date = date;
    // bsm.volatility = 0.1;
    bsm.riskFreeRate = r;
    bsm.stockPrice = S;
    bsm.date = date;

    auto priceFunc = [&bsm, &callOption] (double vol) {
        bsm.volatility = vol;
        MultiStockModel msm(bsm);
        return callOption.price(msm);
    };

    return bisectionRecursion(priceFunc, a, b, price, threshold);
}

void testImpliedVolatility() {
    double strike = 105.0;
    double maturity = 2.0;
    double rate = 0.05;
    double stockPrice = 100.0;
    double date = 1.0;

    double expectedVol = 0.1;

    CallOption callOption;
    callOption.setStrike( strike );
    callOption.setMaturity( maturity );
    
    BlackScholesModel bsm;
    bsm.date = date;
    bsm.volatility = expectedVol;
    bsm.riskFreeRate = rate;
    bsm.stockPrice = stockPrice;

	MultiStockModel msm(bsm);

    double price = callOption.price( msm );
    double vol = impliedVolatility(stockPrice, rate, strike, date, maturity, price, 0, 0.9, 0.001);

    ASSERT_APPROX_EQUAL( vol, expectedVol, 0.01);
}