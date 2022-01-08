#include "UpAndOutOption.h"
#include "MonteCarloPricer.h"

using namespace std;

double UpAndOutOption::payoff(
        const std::vector<double>& prices ) const {
    int n = prices.size();
    for (int i=0; i<n; i++) {
        if (prices[i]>getBarrier()) {
            return 0.0;
        }
    }
    double stockAtMaturity = prices.back();
    if (stockAtMaturity>getStrike()) {
        return stockAtMaturity-getStrike();
    } else {
        return 0.0;
    }
}


/////////////////////////////////////
//
//   TESTS
//
/////////////////////////////////////


void testPayoff() {
    UpAndOutOption o;
    o.setBarrier(100);
    o.setStrike(70);
    vector<double> prices;
    prices.push_back(120);
    prices.push_back(80);
    ASSERT_APPROX_EQUAL( o.payoff( prices ), 0.0, 0.001);
    prices[0] = 90;
    ASSERT_APPROX_EQUAL( o.payoff( prices ), 10.0, 0.001);
    prices[1] = 60;
    ASSERT_APPROX_EQUAL( o.payoff( prices ), 0.0, 0.001);
}


static void testPerformance() {
	BlackScholesModel model;
	model.stockPrice = 100;
	model.volatility = 0.1;

	UpAndOutOption o;
	o.setBarrier(120);
	o.setStrike(110);
	o.setMaturity(1.0);

	MonteCarloPricer pricer;
	clock_t start = clock();
	pricer.nScenarios = 1000;
	pricer.nSteps = 365;

	double price = pricer.price(o, model);
	double elapsed = (double)(clock() - start);
	std::cout << "Price " << price << "\n";
	std::cout << "Pricing took " << (elapsed / CLOCKS_PER_SEC) << "s\n";
}


void testUpAndOutOption() {
	TEST(testPayoff);
	TEST(testPerformance);
}