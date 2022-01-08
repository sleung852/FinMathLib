#include "MonteCarloPricer.h"
#include "BlackScholesModel.h"
#include "matlib.h"
#include "CallOption.h"

using namespace std;

MonteCarloPricer::MonteCarloPricer() :
    nScenarios(10000),
    nSteps(10) {
}

double MonteCarloPricer::price(
        const ContinuousTimeOption& option,
        const StockPriceModel& model ) {
    int nSteps = this->nSteps;
    if (!option.isPathDependent()) {
        nSteps = 1;
    }
    double total = 0.0;
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
            generateRiskNeutralPricePath(
                option.getMaturity(),
                nSteps );
        double payoff = option.payoff( path );
        total+= payoff;
    }
    double mean = total/nScenarios;
    double r = model.getRiskFreeRate();
    double T = option.getMaturity() - model.getDate();
    return exp(-r*T)*mean;
}

double MonteCarloPricer::delta(
        const ContinuousTimeOption& option,
        StockPriceModel model,
        double h) {

    double total = 0.0;

    for (int i=0; i<nScenarios; i++) {
        model.setStockPrice(model.getStockPrice()+h);
        vector<double> pathDeltaPlusH = model.
                generateRiskNeutralPricePath(
                    option.getMaturity(),
                    1);
        model.setStockPrice(model.getStockPrice()-2*h);
        vector<double> pathDeltaMinusH = model.
                generateRiskNeutralPricePath(
                    option.getMaturity(),
                    1);
        double payoffPlusH=option.payoff(pathDeltaPlusH);
        double payoffMinusH=option.payoff(pathDeltaMinusH);
        total += (payoffPlusH - payoffMinusH)/(2*h);
    }
    double mean = total/nScenarios;
    double r = model.getRiskFreeRate();
    double T = option.getMaturity() - model.getDate();
    return exp(-r*T)*mean;
}

//////////////////////////////////////
//
//   Tests
//
//////////////////////////////////////

static void testPriceCallOption() {
    rng("default");

    CallOption c;
    c.setStrike( 110 );
    c.setMaturity( 2 );

    BlackScholesModel m;
    m.setVolatility(0.1);
    m.setRiskFreeRate(0.05);
    m.setStockPrice(100.0);
    m.setDrift(0.1);
    m.setDate(1);

    MonteCarloPricer pricer;
    double price = pricer.price( c, m );
    double expected = c.price( m );
    ASSERT_APPROX_EQUAL( price, expected, 0.1 );
}

void testMonteCarloPricer() {
    testPriceCallOption();
}