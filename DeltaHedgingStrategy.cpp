#include "DeltaHedgingStrategy.h"
#include "BlackScholesModel.h"
#include "CallOption.h"
#include "MultiStockModel.h"
#include "testing.h"
#include <memory>

using namespace std;

Matrix DeltaHedgingStrategy::selectStockQuantity(double date, Matrix stockPrices) {
    Matrix deltas(stockPrices.nRows(), 1);
    for (size_t i=0; i<stockPrices.nRows(); i++) {
        BlackScholesModel pm = *getPricingModel();
        pm.stockPrice = stockPrices(i);
        pm.date = date;
        deltas(i) = toHedge->delta(pm);
    }
	return deltas;
}

double DeltaHedgingStrategy::selectStockQuantity(double date, double stockPrice) {
    BlackScholesModel pm = *getPricingModel();
    pm.stockPrice = stockPrice;
    pm.date = date;
    return toHedge->delta(pm);
}

static void testDeltaHedgingStrategyChooseCharge() {
    shared_ptr<BlackScholesModel> model = make_shared<BlackScholesModel>();
	model->stockPrice = 1;
	model->date = (0);
	model->riskFreeRate=(0.05);
	model->volatility=(0.2);
	model->drift=(0.10);

    MultiStockModel msm(*model);

    shared_ptr<CallOption> option = make_shared<CallOption>();
    option->setStrike(model->stockPrice);
	option->setMaturity(1);

    DeltaHedgingStrategy strat = DeltaHedgingStrategy();
    strat.setToHedge(option);
    strat.setPricingModel(model);

    stringstream ss;
    ss << "Charge Set: " << strat.chooseCharge(model->stockPrice, option);
    DEBUG_PRINT(ss.str());

    ASSERT (option->price(msm) == strat.chooseCharge(model->stockPrice, option) );
}

void testDeltaHedgingStrategy(){
    // TEST (testDeltaHedgingStrategyConstructor);
    // TEST (testDeltaHedgingStrategySetup);
    // setDebugEnabled(true);
    TEST (testDeltaHedgingStrategyChooseCharge);
    // setDebugEnabled(false);
}