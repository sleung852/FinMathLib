#include "AsianPutOption.h"
#include "AsianOption.h"
#include "BlackScholesModel.h"
#include "matlib.h"
#include "MonteCarloPricer.h"
#include "PutOption.h"

Matrix AsianPutOption::payoff(const Matrix&prices) const {
	Matrix mean = meanRows(prices);
	Matrix payoff = getStrike() - mean;
    Matrix mask = payoff > 0;
	payoff.times(mask);
	return payoff;
}

static void testMonteCarloPriceAsianPut() {
	rng("default");
	AsianPutOption option;
	option.setMaturity(1.0);
	option.setStrike(100.0);
	BlackScholesModel model;
	model.stockPrice = 95;
	model.volatility = 0.1;
	model.drift = 0.0;
	model.riskFreeRate = 0.0;
	MonteCarloPricer pricer;
	pricer.nSteps = 100;
	pricer.nScenarios = 3;
	double price = pricer.price(option, model);

	PutOption putOption;
	putOption.setMaturity(1.0);
	putOption.setStrike(100.0);
	MultiStockModel msm(model);
	double europeanPrice = putOption.price(msm);
	// without studying any theory on asian options we
	// can't guess much about the price, but it is presumably
	// not too wildly different from the european option price
	assert(price > 0);
	assert(price < 2*europeanPrice);
}

void testAsianPutOption() {
	TEST(testMonteCarloPriceAsianPut);
}
