#include "HedgingSimulator.h"
#include "testing.h"
#include "matlib.h"

using namespace std;

HedgingSimulator::HedgingSimulator() {
	// Choose default models and options
	shared_ptr<BlackScholesModel> model(
		new BlackScholesModel());
	model->stockPrice = 1;
	model->date = 0;
	model->riskFreeRate = 0.05;
	model->volatility = 0.2;
	model->drift = 0.10;

	shared_ptr<CallOption> option(new CallOption());
	option->setStrike(model->stockPrice);
	option->setMaturity(1);

	setToHedge(option);
	setSimulationModel(model);
	setPricingModel(model);

	nSteps = 10;
}

/*  Runs a number of simulations and returns
a vector of the profit and loss */
std::vector<double>
  HedgingSimulator::runSimulations(int nSimulations)
		    const {
	std::vector<double> ret(nSimulations);
	for (int i = 0; i < nSimulations; i++) {
		ret[i] = runSimulation();
	}
	return ret;
}
/*  Run a simulation and compute the profit and loss */
double HedgingSimulator::runSimulation() const {
	double T = toHedge->getMaturity();
	double S0 = simulationModel->stockPrice;
	vector<double> pricePath = 
		simulationModel->generatePricePath(T,nSteps);

	double dt = T / nSteps;
	double charge = chooseCharge(S0);
	double stockQuantity = selectStockQuantity(0,S0);
	double bankBalance = charge - stockQuantity*S0;
	for (int i = 0; i< nSteps-1; i++) {
		double interest = bankBalance *
			exp(simulationModel->riskFreeRate*dt);
		double S = pricePath[i];
		double date = dt*(i + 1);
		double newStockQuantity
			= selectStockQuantity(date, S);
		double costs
			= (newStockQuantity - stockQuantity)*S;
		bankBalance = bankBalance + interest - costs;
		stockQuantity = newStockQuantity;
	}
	double interest = bankBalance *
		exp(simulationModel->riskFreeRate*dt);
	double S = pricePath[nSteps];
	double stockValue = stockQuantity*S;
	double payout = toHedge->payoff(S);
	return bankBalance +interest
			+stockValue - payout;
}

/*  How much should we charge the customer */
double HedgingSimulator::chooseCharge(
		double stockPrice) const {
	// create a copy of the pricing model
	BlackScholesModel pm = *pricingModel;
	pm.stockPrice = stockPrice;
	return toHedge->price(pm);
}

/*  How much stock should we hold */
double HedgingSimulator::selectStockQuantity(
		double date,
		double stockPrice) const {
	// create a copy of the pricing model
	BlackScholesModel pm = *pricingModel;
	pm.stockPrice = stockPrice;
	pm.date = date;
	return toHedge->delta(pm);
}



//
//
//   Tests
//
//


static void testDeltaHedgingMeanPayoff() {
	rng("default");
	HedgingSimulator simulator;
	simulator.setNSteps(1000);
	vector<double> result
		= simulator.runSimulations(1);
	ASSERT_APPROX_EQUAL(result[0], 0.0, 0.01);
}

static void testPlotDeltaHedgingHistogram() {
	rng("default");
	HedgingSimulator simulator;
	simulator.setNSteps(100);
	vector<double> result =
		simulator.runSimulations(10000);
	hist("deltaHedgingPNL.html", result, 20);
}
void testHedgingSimulator() {
	TEST(testDeltaHedgingMeanPayoff);
	TEST(testPlotDeltaHedgingHistogram);
}