#pragma once

#include "stdafx.h"
#include "StockPriceModel.h"
#include "ContinuousTimeOptionBase.h"
#include "Strategy.h"

/**
 *   This class can be used to see the results of the delta
 *   hedging strategy
 */
class HedgingSimulator {
public:
	/*  Runs a number of simulations and returns
	    a vector of the profit and loss */
	std::vector<double> runSimulations(
			int nSimulations ) const;

	double meanAbsolutePnL( int nSimulations) const;

	void setToHedge(
			std::shared_ptr<ContinuousTimeOptionBase> toHedge) {
		this->toHedge = toHedge;
	}
	void setSimulationModel(
		std::shared_ptr<StockPriceModel> model) {
		this->simulationModel = model;
	}
	// void setPricingModel(
	// 	std::shared_ptr<StockPriceModel> model) {
	// 	this->pricingModel = model;
	// }
	void setNSteps(int nSteps) {
		this->nSteps = nSteps;
	}
	void setBidProportion(double p) {
		this->bidProportion = p;
	}
	void setHedgingStrategy(
		std::shared_ptr<Strategy> strategy) {
		this->hedgingStrategy = strategy;
	}

	/*  Another constructor */
	HedgingSimulator(std::shared_ptr<ContinuousTimeOptionBase> option,
					 std::shared_ptr<StockPriceModel> model,
					 std::shared_ptr<Strategy> strategy);
	HedgingSimulator(std::shared_ptr<ContinuousTimeOptionBase> option,
					 std::shared_ptr<StockPriceModel> model);
	/*  Default constructor */
	HedgingSimulator(std::shared_ptr<ContinuousTimeOptionBase> option);

private:
	/*  The option that has been written */
	std::shared_ptr<ContinuousTimeOptionBase> toHedge;
	/*  The model used to simulate stock prices */
	std::shared_ptr<StockPriceModel>
		simulationModel;
	/* The model used to compute prices and deltas */
	// std::shared_ptr<StockPriceModel> pricingModel;
	/* Hedging strategy */
	std::shared_ptr<Strategy> hedgingStrategy;
	/*  The number of steps to use */
	int nSteps;
	/* bidProportion accounts for constant bid-ask spread */
	double bidProportion;
	/*  Run a simulation and compute
		the profit and loss */
	double runSimulation() const;
	/*  How much should we charge the customer */
	// double chooseCharge( double stockPrice ) const;
	/*  Hoe much stock should we hold */
	// double selectStockQuantity(
	// 	double date,
	// 	double stockPrice ) const;
	/* Accounts price difference in bid ask spread */
	double computePrice( bool buy, double stockPrice) const;
};

//
//
//     Tests
//
//


void testHedgingSimulator();