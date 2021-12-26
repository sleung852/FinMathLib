#include "options.h"
#include "testing.h"

// Black-scholes put option
double blackScholesPutPrice(double strike, double t, double spot, double volatility, double riskfreerate) {
    double d1 = (log(spot/strike) + (riskfreerate + pow(volatility, 2.0)/2) * t) / (volatility * sqrt(t));
    double d2 = d1 - volatility * sqrt(t);
    return strike * exp(-riskfreerate * t) * normcdf(-d2) - spot * normcdf(-d1);
}

// Black-scholes call option
double blackScholesCallPrice(double strike, double t, double spot, double volatility, double riskfreerate) {
    double d1 = (log(spot/strike) + (riskfreerate + pow(volatility, 2.0)/2) * t) / (volatility * sqrt(t));
    double d2 = d1 - volatility * sqrt(t);
    return normcdf(d1) * spot - normcdf(d2) * strike * exp(-riskfreerate * t);
}

// test

static void test_blackScholesPutPrice() {
    double strike = 105;
    double t = 1;
    double spot = 100;
    double volatility = 0.15;
    double riskfreerate = 0.02;
    // Call Put Parity
    DEBUG_PRINT("Call Put Parity Test:\n")
    ASSERT_APPROX_EQUAL(blackScholesCallPrice(strike, t, spot, volatility, riskfreerate)+strike/pow(1+riskfreerate, t),
                        spot+blackScholesPutPrice(strike, t, spot, volatility, riskfreerate),
                        0.05);
    // increaing test - higher volitality, pricer the options
    DEBUG_PRINT("Volatility Test:\n")
    ASSERT(blackScholesPutPrice(strike, t, spot, volatility+0.01, riskfreerate) > blackScholesPutPrice(strike, t, spot, volatility, riskfreerate));
}

void testOptions() {
    setDebugEnabled(true);
    TEST(test_blackScholesPutPrice);
    setDebugEnabled(false);
}

