#include "PutOption.h"
#include "BlackScholesModel.h"
#include "matlib.h"

double PutOption::payoff( double stockAtMaturity ) const {
    if (stockAtMaturity<getStrike()) {
        return getStrike()-stockAtMaturity;
    } else {
        return 0.0;
    }
}

double PutOption::price(
        const StockPriceModel& bsm ) const {
    double S = bsm.getStockPrice();
    double K = getStrike();
    double sigma = bsm.getVolatility();
    double r = bsm.getRiskFreeRate();
    double T = getMaturity() - bsm.getDate();

    double numerator = log( S/K ) + ( r + sigma*sigma*0.5)*T;
    double denominator = sigma * sqrt(T );
    double d1 = numerator/denominator;
    double d2 = d1 - denominator;
    return -S*normcdf(-d1) + exp(-r*T)*K*normcdf(-d2);
}

double PutOption::delta(
	const StockPriceModel& bsm) const {
	double S = bsm.getStockPrice();
	double K = getStrike();
	double sigma = bsm.getVolatility();
	double r = bsm.getRiskFreeRate();
	double T = getMaturity() - bsm.getDate();

	double numerator=log(S/K)+(r+sigma*sigma*0.5)*T;
	double denominator = sigma * sqrt(T);
	double d1 = numerator / denominator;
	return normcdf(d1) - 1;
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
    bsm.setDate(1.0);
    bsm.setVolatility(0.1);
    bsm.setRiskFreeRate(0.05);
    bsm.setStockPrice(100.0);

    double price = putOption.price( bsm );
    ASSERT_APPROX_EQUAL( price, 3.925, 0.01);
}

void testPutOption() {
    TEST( testPutOptionPrice );
    TEST( testPayoff );
}
