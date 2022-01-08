#include "HedgingSimulator.h"
#include "ContinuousTimeOptionBase.h"
#include "testing.h"
#include "matlib.h"
#include "LineChart.h"
#include "Histogram.h"
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesModel.h"
#include "TwoLevelModel.h"
#include "DeltaHedgingStrategy.h"
#include "BondsOnlyStrategy.h"
#include "StockOnlyStrategy.h"
#include <memory>

using namespace std;

/*  Another constructor */
HedgingSimulator::HedgingSimulator(std::shared_ptr<ContinuousTimeOptionBase> option,
	std::shared_ptr<StockPriceModel> model, std::shared_ptr<Strategy> strategy) {
		setToHedge(option);
		setSimulationModel(model);
		strategy->setPricingModel(model);
		setHedgingStrategy(strategy);
		// default values
		nSteps = 10;
		setBidProportion(1.0);
}

HedgingSimulator::HedgingSimulator(std::shared_ptr<ContinuousTimeOptionBase> option,
	std::shared_ptr<StockPriceModel> model) {
		setToHedge(option);
		setSimulationModel(model);
		// default values
		nSteps = 10;
		setBidProportion(1.0);
}

HedgingSimulator::HedgingSimulator(shared_ptr<ContinuousTimeOptionBase> option) {
	// Choose default models and options
	shared_ptr<BlackScholesModel> model(new BlackScholesModel());
	model->setStockPrice(1);
	model->setDate(0);
	model->setRiskFreeRate(0.05);
	model->setVolatility(0.2);
	model->setDrift(0.10);

	option->setStrike(model->getStockPrice());
	option->setMaturity(1);

	setToHedge(option);
	setSimulationModel(model);
	// setPricingModel(model);
	nSteps = 10;
	setBidProportion(1.0);

	shared_ptr<DeltaHedgingStrategy> strategy = make_shared<DeltaHedgingStrategy>();
    strategy->setToHedge(option);
    strategy->setPricingModel(model);
	setHedgingStrategy(strategy);
}

/*  Runs a number of simulations and returns
a vector of the profit and loss */
std::vector<double>
    HedgingSimulator::runSimulations(
						   int nSimulations) const {
	std::vector<double> ret(nSimulations);
	for (int i = 0; i < nSimulations; i++) {
		ret[i] = runSimulation();
	}
	return ret;
}
/*  Runs a number of simulations and returns
the absolute mean value of the profit and loss */
double HedgingSimulator::meanAbsolutePnL( int nSimulations) const {
	return mean(runSimulations(nSimulations));
}

/*  Run a simulation and compute the profit and loss */
double HedgingSimulator::runSimulation() const {
	double T = toHedge->getMaturity();
	double S0 = simulationModel->getStockPrice();
	vector<double> pricePath = 
		simulationModel->generatePricePath(T,nSteps);

	double dt = T / nSteps;
	// hedgingStrategy->setPricingModel(pricingModel);
	double charge = hedgingStrategy->chooseCharge(S0, toHedge);
	double stockQuantity = hedgingStrategy->selectStockQuantity(0, S0);
	// double stockQuantity = selectStockQuantity(0,S0);
	double bankBalance = charge - stockQuantity*S0;
	for (int i = 0; i< nSteps-1; i++) {
		double balanceWithInterest = bankBalance *
			exp(simulationModel->getRiskFreeRate()*dt);
		double S = pricePath[i];
		double date = dt*(i + 1);
		double newStockQuantity = hedgingStrategy->
			selectStockQuantity(date, S);
		double changeInStockQuantity =
			newStockQuantity - stockQuantity;
		double stockPrice = 
			computePrice((changeInStockQuantity < 0), S);
		double costs = changeInStockQuantity*stockPrice;
		bankBalance = balanceWithInterest - costs;
		stockQuantity = newStockQuantity;
	}
	double balanceWithInterest = bankBalance *
		exp(simulationModel->getRiskFreeRate()*dt);
	double S = pricePath[nSteps - 1];
	double stockValue = stockQuantity*S;
	// double payout = toHedge->payoff(S);
	double payout = toHedge->payoff(pricePath);
	return balanceWithInterest + stockValue - payout;
}

double HedgingSimulator::computePrice( bool buy, double stockPrice) const {
	if (buy) return stockPrice;
	else return stockPrice * bidProportion;
}

// /*  How much should we charge the customer */
// double HedgingSimulator::chooseCharge(
// 						double stockPrice) const {
// 	// create a copy of the pricing model
// 	StockPriceModel pm = *pricingModel;
// 	pm.setStockPrice(stockPrice);
// 	return toHedge->price(pm);
// }
// /*  How much stock should we hold */
// double HedgingSimulator::selectStockQuantity(
// 		double date,
// 		double stockPrice) const {
// 	// create a copy of the pricing model
// 	StockPriceModel pm = *pricingModel;
// 	pm.setStockPrice(stockPrice);
// 	pm.setDate(date);
// 	return toHedge->delta(pm);
// }

/*
Functions for visualisation purposes
*/

void plotChangeInSigmaPlot(string title,
					double nSimulations,
					string fileName,
					double bidProportion) {
	shared_ptr<CallOption> option = make_shared<CallOption>();
	HedgingSimulator simulator(option);
	shared_ptr<TwoLevelModel> model = make_shared<TwoLevelModel>();
	model->setStockPrice(1);
	model->setDate(0);
	model->setRiskFreeRate(0.05);
	model->setVolatility(0.2);
	// model->setVolatility2(0.4);
	model->setDrift(0.10);
	simulator.setSimulationModel(model);

	vector<double> sigmas = linspace(0.0, 0.4, 20);
	vector<double> meanPnL(sigmas.size());

	simulator.setNSteps(1000);

	simulator.setBidProportion(bidProportion);
	for (int i=0; i<meanPnL.size(); i++) {
		model->setVolatility2(sigmas[i]);
		meanPnL.at(i) = simulator.meanAbsolutePnL(nSimulations);
	}
	LineChart lChart;
	lChart.setTitle(title);
	lChart.setSeries(sigmas, meanPnL);
	lChart.writeAsHTML(fileName);
}

void plotLogLogPlot(string title,
					double nSimulations,
					string fileName,
					double bidProportion) {
	shared_ptr<CallOption> option = make_shared<CallOption>();
	HedgingSimulator simulator(option);
	vector<double> frequencies = linspace(100, 1000, 10);
	vector<double> meanPnL(frequencies.size());
	simulator.setBidProportion(bidProportion);
	for (int i=0; i<meanPnL.size(); i++) {
		simulator.setNSteps(frequencies.at(i));
		meanPnL.at(i) = simulator.meanAbsolutePnL(nSimulations);
	}
	LineChart lChart;
	lChart.setTitle(title);
	lChart.setSeries(frequencies, meanPnL);
	lChart.writeAsHTML(fileName);
}

void plotLogLogPlot(string title,
					double nSimulations,
					string fileName) {
	plotLogLogPlot(title, nSimulations, fileName, 1.0);
}

void plotHedgingStrategyHistogram(string title, double nSimulations, string fileName,
	shared_ptr<StockPriceModel> model, shared_ptr<ContinuousTimeOptionBase> option,
	shared_ptr<Strategy> strategy) {
	// define 
	HedgingSimulator simulator(option, model, strategy);
	simulator.setNSteps(100);
	vector<double> result = simulator.runSimulations(10000);
	Histogram histogram;
	histogram.setTitle(title);
	histogram.setNumBuckets(20);
	histogram.setData(result);
	histogram.writeAsHTML(fileName);
}


//
//
//   Tests
//
//


static void testCallOptionDeltaHedgingMeanPayoff() {
  rng("default");
  shared_ptr<CallOption> option = make_shared<CallOption>();
  HedgingSimulator simulator(option);
  simulator.setNSteps(1000);
  vector<double> result=simulator.runSimulations(1);
  ASSERT_APPROX_EQUAL(result[0], 0.0, 0.01);
}

static void testPlotDeltaHedgingHistogram() {
	rng("default");
	shared_ptr<CallOption> option = make_shared<CallOption>();
	HedgingSimulator simulator(option);
	simulator.setNSteps(100);
	vector<double> result =
		simulator.runSimulations(10000);
	hist("deltaHedgingPNL.html", result, 20);
}

static void testPlotLogLogPlot() {
	rng("default");
	plotLogLogPlot("Log-Log Plot", 1000, "loglogplotv1.html");
}

static void testPlotLogLogPlotWithBidAskSpread() {
	rng("default");
	plotLogLogPlot("Log-Log Plot with P=0.001", 1000, "loglogplotv2.html", 0.001);
}

static void testPutOptionDeltaHedgingMeanPayoff() {
	rng("default");
	shared_ptr<PutOption> option = make_shared<PutOption>();
	HedgingSimulator simulator(option);
	simulator.setNSteps(1000);
	vector<double> result=simulator.runSimulations(1);
	ASSERT_APPROX_EQUAL(result[0], 0.0, 0.01);
}

static void testDeltaHedgingWithAdjustingSigmasPlot() {
	rng("default");
	plotChangeInSigmaPlot("Change in Sigmas",
						1000,
						"changeInSigma.html",
						1.0);
}

static void testHedgingStrategiesWithHistogram1() {
	shared_ptr<BlackScholesModel> model = make_shared<BlackScholesModel>();
	model->setStockPrice(1.0);
	model->setDate(0.0);
	model->setRiskFreeRate(0.0);
	model->setVolatility(0.5);
	model->setDrift(0.01);
	shared_ptr<PutOption> option = make_shared<PutOption>();
	option->setMaturity(1);
	option->setStrike(1);
	shared_ptr<BondsOnlyStrategy> bondOnlyStrategy = make_shared<BondsOnlyStrategy>();
	plotHedgingStrategyHistogram("Bond Only Strategy sigma=0.5 mu=0.01", 1000, "bondOnlyStrategy1.html",
	model, option, bondOnlyStrategy);
	shared_ptr<StockOnlyStrategy> stockOnlyStrategy = make_shared<StockOnlyStrategy>();
	plotHedgingStrategyHistogram("Stock Only Strategy sigma=0.5 mu=0.01", 1000, "stockOnlyStrategy1.html",
	model, option, stockOnlyStrategy);
	shared_ptr<DeltaHedgingStrategy> deltaHedgingStrategy = make_shared<DeltaHedgingStrategy>();
	deltaHedgingStrategy->setToHedge(option);
	plotHedgingStrategyHistogram("Delta Hedging Strategy sigma=0.5 mu=0.01", 1000, "deltaHedgingStrategy1.html",
	model, option, deltaHedgingStrategy);
}

static void testHedgingStrategiesWithHistogram2() {
	shared_ptr<BlackScholesModel> model = make_shared<BlackScholesModel>();
	model->setStockPrice(1.0);
	model->setDate(0.0);
	model->setRiskFreeRate(0.0);
	model->setVolatility(0.01);
	model->setDrift(0.5);
	shared_ptr<PutOption> option = make_shared<PutOption>();
	option->setMaturity(1);
	option->setStrike(1);
	shared_ptr<BondsOnlyStrategy> bondOnlyStrategy = make_shared<BondsOnlyStrategy>();
	plotHedgingStrategyHistogram("Bond Only Strategy sigma=0.01 mu=0.5", 1000, "bondOnlyStrategy2.html",
	model, option, bondOnlyStrategy);
	shared_ptr<StockOnlyStrategy> stockOnlyStrategy = make_shared<StockOnlyStrategy>();
	plotHedgingStrategyHistogram("Stock Only Strategy sigma=0.01 mu=0.5", 1000, "stockOnlyStrategy2.html",
	model, option, stockOnlyStrategy);
	shared_ptr<DeltaHedgingStrategy> deltaHedgingStrategy = make_shared<DeltaHedgingStrategy>();
	deltaHedgingStrategy->setToHedge(option);
	plotHedgingStrategyHistogram("Delta Hedging Strategy sigma=0.01 mu=0.5", 1000, "deltaHedgingStrategy2.html",
	model, option, deltaHedgingStrategy);
}

void testHedgingSimulator() {
	TEST(testCallOptionDeltaHedgingMeanPayoff);
	TEST(testPlotDeltaHedgingHistogram);
	TEST(testPlotLogLogPlot);
	TEST(testPlotLogLogPlotWithBidAskSpread);
	TEST(testPutOptionDeltaHedgingMeanPayoff);
	// setDebugEnabled(true);
	TEST(testDeltaHedgingWithAdjustingSigmasPlot);
	// setDebugEnabled(false);
	TEST(testHedgingStrategiesWithHistogram1);
	TEST(testHedgingStrategiesWithHistogram2);
}