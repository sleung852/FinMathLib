#include "CallOption.h"
#include "matlib.h"

using namespace std;

Matrix CallOption::payoffAtMaturity( const Matrix& stockAtMaturity ) const {
    Matrix val = stockAtMaturity - getStrike();
    val.positivePart();
    return val;
}


double CallOption::price( 
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
    return S*normcdf(d1) - exp(-r*T)*K*normcdf(d2);
}


std::ostream& operator<<(std::ostream& out, const CallOption& callOption ) {
    vector<string> params({"Maturity", "Strike"});
    vector<double> values({callOption.getMaturity(), callOption.getStrike()});
    out << callOption.describe(callOption.optionName, params, values);
    return out;
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

    double price = callOption.price( bsm );
    ASSERT_APPROX_EQUAL( price, 4.046, 0.01);
}

static void testCallOptionOStream() {
    CallOption callOption;
    callOption.setStrike( 105.0 );
    callOption.setMaturity( 2.0 );
    
    cout << callOption << endl;
    
}

void testCallOption() {
    TEST( testCallOptionPrice );
    TEST( testCallOptionOStream );
}
