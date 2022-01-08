#include "ImpliedVolatility.h"
#include "BlackScholesModel.h"
#include "MultiStockModel.h"
#include "CallOption.h"
#include <memory>
#include "matlib.h"

using namespace std;

double impliedVolatility(std::shared_ptr<ContinuousTimeOptionBase> option, BlackScholesModel model,
    double price, double threshold, double maxVol)  {

    auto priceFunc = [model, option] (double vol) {
        BlackScholesModel bsm(model);
        bsm.volatility = vol;
        MultiStockModel msm(bsm);
        return option->price(msm);
    };

    return bisectionRecursion(priceFunc, 0.0, maxVol, price, threshold);
}

static void testImpliedVolatilityCallOption() {
    double strike = 105.0;
    double maturity = 2.0;
    double rate = 0.05;
    double stockPrice = 100.0;
    double date = 1.0;

    double expectedVol = 0.1;

    shared_ptr<CallOption> callOption = make_shared<CallOption>();
    callOption->setStrike( strike );
    callOption->setMaturity( maturity );
    
    BlackScholesModel bsm;
    bsm.date = date;
    bsm.volatility = expectedVol;
    bsm.riskFreeRate = rate;
    bsm.stockPrice = stockPrice;

    MultiStockModel msm(bsm);
    double price = callOption->price(msm);
    double vol = impliedVolatility(callOption, bsm, price);

    ASSERT_APPROX_EQUAL( vol, expectedVol, 0.01);
}

void testImpliedVolatility() {
    TEST (testImpliedVolatilityCallOption);
}