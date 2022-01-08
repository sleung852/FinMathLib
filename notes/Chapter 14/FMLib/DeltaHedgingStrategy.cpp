#include "DeltaHedgingStrategy.h"
#include "BlackScholesModel.h"
#include "CallOption.h"
#include "testing.h"
#include <memory>

using namespace std;

double DeltaHedgingStrategy::selectStockQuantity(double date, double stockPrice) {
	StockPriceModel pm = *getPricingModel();
	pm.setStockPrice(stockPrice);
	pm.setDate(date);
	return toHedge->delta(pm);
}

// double DeltaHedgingStrategy::chooseCharge(double stockPrice,  std::shared_ptr<ContinuousTimeOptionBase> option) {
// 	StockPriceModel pm = *getPricingModel();
//     pm.setStockPrice(stockPrice);
// 	return option->price(pm);
// }

/*  Simple Debuggin */

// static void testDeltaHedgingStrategyConstructor() {
//     DeltaHedgingStrategy strat = DeltaHedgingStrategy();
// }

// static void testDeltaHedgingStrategySetup() {
//     DeltaHedgingStrategy strat = DeltaHedgingStrategy();

//     shared_ptr<BlackScholesModel> model = make_shared<BlackScholesModel>();
// 	model->setStockPrice(1);
// 	model->setDate(0);
// 	model->setRiskFreeRate(0.05);
// 	model->setVolatility(0.2);
// 	model->setDrift(0.10);

//     shared_ptr<CallOption> option = make_shared<CallOption>();
//     option->setStrike(model->getStockPrice());
// 	option->setMaturity(1);

//     // strat.setToHedge(option);
//     // strat.setPricingModel(model);  
// }

static void testDeltaHedgingStrategyChooseCharge() {
    shared_ptr<BlackScholesModel> model = make_shared<BlackScholesModel>();
	model->setStockPrice(1);
	model->setDate(0);
	model->setRiskFreeRate(0.05);
	model->setVolatility(0.2);
	model->setDrift(0.10);

    shared_ptr<CallOption> option = make_shared<CallOption>();
    option->setStrike(model->getStockPrice());
	option->setMaturity(1);

    DeltaHedgingStrategy strat = DeltaHedgingStrategy();
    strat.setToHedge(option);
    strat.setPricingModel(model);

    stringstream ss;
    ss << "Charge Set: " << strat.chooseCharge(model->getStockPrice(), option);
    DEBUG_PRINT(ss.str());

    ASSERT (option->price(*model) == strat.chooseCharge(model->getStockPrice(), option) );
}

void testDeltaHedgingStrategy(){
    // TEST (testDeltaHedgingStrategyConstructor);
    // TEST (testDeltaHedgingStrategySetup);
    // setDebugEnabled(true);
    TEST (testDeltaHedgingStrategyChooseCharge);
    // setDebugEnabled(false);
}