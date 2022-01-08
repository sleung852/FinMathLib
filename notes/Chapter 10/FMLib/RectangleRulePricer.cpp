#include "RectangleRulePricer.h"
#include "RealFunction.h"
#include "geometry.h"
#include "matlib.h"
#include "CallOption.h"

static bool isfinitenumber(double arg) {
	return arg == arg &&
		arg != std::numeric_limits<double>::infinity() &&
		arg != -std::numeric_limits<double>::infinity();
}

double RectangleRulePricer::price(const PathIndependentOption& option, const BlackScholesModel& bsm) const {
    // compute the log asset price distribution

    class PayoffDistribution : public RealFunction {
        public:
            PayoffDistribution(const PathIndependentOption& option, const BlackScholesModel& bsm) :
                option(option), bsm(bsm){
            }
            const PathIndependentOption& option;
            const BlackScholesModel& bsm;

            double evaluate(double x) {
                double sigma = bsm.volatility;
                double S0 = bsm.stockPrice;
                double mu = bsm.riskFreeRate - 0.5*sigma*sigma;
                double t = option.getMaturity();

                double probability = 1 / (sigma * sqrt(2*PI*t)) * exp(-pow(x-log(S0)-mu*t,2)/(2*sigma*sigma*t));
                double payoff = option.payoff(exp(x));
                if (isfinitenumber(payoff)) {
                    return payoff * probability;
                }
                else {
                    return 0.0;
                }
            }
    };

    PayoffDistribution payoffDistribution(option, bsm);
    // double expectedFuturePayoff = integralToInfinity(payoffDistribution, 0, 1000);
    double expectedFuturePayoff = integralFromInfinityToInfinity(payoffDistribution, 1000);
    return expectedFuturePayoff * exp(-bsm.riskFreeRate*option.getMaturity());
}


// static void testRectangleRulePricerCallOption() {
//     CallOption callOption;
//     callOption.strike = 105.0;
//     callOption.maturity = 2.0;
    
//     BlackScholesModel bsm;
//     bsm.date = 1.0;
//     bsm.volatility = 0.1;
//     bsm.riskFreeRate = 0.05;
//     bsm.stockPrice = 100.0;

//     double price = callOption.price( bsm );

//     RectangleRulePricer pricer;
//     double priceRect = pricer.price(callOption, bsm);

//     ASSERT_APPROX_EQUAL( priceRect, price, 0.01);
// }

void testRectangleRulePricer() {
    // TEST( testRectangleRulePricerCallOption );
}