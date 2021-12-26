#include "MonteCarloPricer.h"

#include "matlib.h"

using namespace std;

MonteCarloPricer::MonteCarloPricer() :
    nScenarios(10000) {
}

// pricing options

double MonteCarloPricer::price(
        const CallOption& callOption,
        const BlackScholesModel& model ) {
    double total = 0.0;
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
                generateRiskNeutralPricePath(
                    callOption.maturity,
                    1 );
        double stockPrice = path.back();
        double payoff=callOption.payoff(stockPrice);
        total+= payoff;
    }
    double mean = total/nScenarios;
    double r = model.riskFreeRate;
    double T = callOption.maturity - model.date;
    return exp(-r*T)*mean;
}

double MonteCarloPricer::price(
        const PutOption& putOption,
        const BlackScholesModel& model ) {
    double total = 0.0;
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
                generateRiskNeutralPricePath(
                    putOption.maturity,
                    1 );
        double stockPrice = path.back();
        double payoff=putOption.payoff(stockPrice);
        total+= payoff;
    }
    double mean = total/nScenarios;
    double r = model.riskFreeRate;
    double T = putOption.maturity - model.date;
    return exp(-r*T)*mean;
}

double MonteCarloPricer::price(
        const UpAndOutOption& uoCallOption,
        const BlackScholesModel& model ) {
    double total = 0.0;
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
                generateRiskNeutralPricePath(
                    uoCallOption.maturity,
                    1 );
        double payoff=uoCallOption.payoff(path);
        total+= payoff;
    }
    double mean = total/nScenarios;
    double r = model.riskFreeRate;
    double T = uoCallOption.maturity - model.date;
    return exp(-r*T)*mean;
}

// pricing deltas

double MonteCarloPricer::delta(
        const CallOption& callOption,
        const BlackScholesModel& model,
        double h) {

    double total = 0.0;

    for (int i=0; i<nScenarios; i++) {
        vector<double> pathDeltaPlusH = model.
                generateRiskNeutralPricePath(
                    callOption.maturity,
                    1,
                    h );
        vector<double> pathDeltaMinusH = model.
                generateRiskNeutralPricePath(
                    callOption.maturity,
                    1,
                    -h );
        double stockPricePlusH = pathDeltaPlusH.back();
        double payoffPlusH=callOption.payoff(stockPricePlusH);
        double stockPriceMinusH = pathDeltaMinusH.back();
        double payoffMinusH=callOption.payoff(stockPriceMinusH);
        total += (payoffPlusH - payoffMinusH)/(2*h);
    }
    double mean = total/nScenarios;
    double r = model.riskFreeRate;
    double T = callOption.maturity - model.date;
    return exp(-r*T)*mean;
}

double MonteCarloPricer::delta(
        const PutOption& putOption,
        const BlackScholesModel& model,
        double h) {

    double total = 0.0;

    for (int i=0; i<nScenarios; i++) {
        rng("default");
        vector<double> pathDeltaPlusH = model.
                generateRiskNeutralPricePath(
                    putOption.maturity,
                    1,
                    h );
        rng("default");
        vector<double> pathDeltaMinusH = model.
                generateRiskNeutralPricePath(
                    putOption.maturity,
                    1,
                    -h );
        double stockPricePlusH = pathDeltaPlusH.back();
        double payoffPlusH=putOption.payoff(stockPricePlusH);
        double stockPriceMinusH = pathDeltaMinusH.back();
        double payoffMinusH=putOption.payoff(stockPriceMinusH);
        total += (payoffPlusH - payoffMinusH)/(2*h);
    }
    double mean = total/nScenarios;
    double r = model.riskFreeRate;
    double T = putOption.maturity - model.date;
    return exp(-r*T)*mean;
}

double MonteCarloPricer::delta(
        const UpAndOutOption& uoCallOption,
        const BlackScholesModel& model,
        double h) {

    double total = 0.0;

    for (int i=0; i<nScenarios; i++) {
        vector<double> pathDeltaPlusH = model.
                generateRiskNeutralPricePath(
                    uoCallOption.maturity,
                    1,
                    h );
        vector<double> pathDeltaMinusH = model.
                generateRiskNeutralPricePath(
                    uoCallOption.maturity,
                    1,
                    -h );
        double payoffPlusH=uoCallOption.payoff(pathDeltaPlusH);
        double payoffMinusH=uoCallOption.payoff(pathDeltaMinusH);
        total += (payoffPlusH - payoffMinusH)/(2*h);
    }
    double mean = total/nScenarios;
    double r = model.riskFreeRate;
    double T = uoCallOption.maturity - model.date;
    return exp(-r*T)*mean;
}

// confidence interval
std::vector<double> MonteCarloPricer::confidenceInterval(
        const CallOption& callOption,
        const BlackScholesModel& model ) {
    double total = 0.0;
    vector<double> payoffs(nScenarios, 0.0);
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
                generateRiskNeutralPricePath(
                    callOption.maturity,
                    1 );
        double stockPrice = path.back();
        double payoff=callOption.payoff(stockPrice);
        total+= payoff;
        payoffs[i] = payoff;
    }
    double mean = total/nScenarios;
    double sd = standardDeviation(payoffs);
    double r = model.riskFreeRate;
    double T = callOption.maturity - model.date;

    double upperBound = exp(-r*T) * (mean - 1.96 * sd / sqrt(nScenarios));
    double lowerBound = exp(-r*T) * (mean + 1.96 * sd / sqrt(nScenarios));

    return vector<double>({upperBound,lowerBound});
}

std::vector<double> MonteCarloPricer::confidenceInterval(
        const PutOption& putOption,
        const BlackScholesModel& model ) {
    double total = 0.0;
    vector<double> payoffs(nScenarios, 0.0);
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
                generateRiskNeutralPricePath(
                    putOption.maturity,
                    1 );
        double stockPrice = path.back();
        double payoff=putOption.payoff(stockPrice);
        total+= payoff;
        payoffs[i] = payoff;
    }
    double mean = total/nScenarios;
    double sd = standardDeviation(payoffs);
    double r = model.riskFreeRate;
    double T = putOption.maturity - model.date;

    double upperBound = exp(-r*T) * (mean - 1.96 * sd / sqrt(nScenarios));
    double lowerBound = exp(-r*T) * (mean + 1.96 * sd / sqrt(nScenarios));

    return vector<double>({upperBound,lowerBound});
}

std::vector<double> MonteCarloPricer::confidenceInterval(
        const UpAndOutOption& uoCallOption,
        const BlackScholesModel& model ) {
    double total = 0.0;
    vector<double> payoffs(nScenarios, 0.0);
    for (int i=0; i<nScenarios; i++) {
        vector<double> path= model.
                generateRiskNeutralPricePath(
                    uoCallOption.maturity,
                    1 );
        double payoff=uoCallOption.payoff(path);
        total+= payoff;
        payoffs[i] = payoff;
    }
    double mean = total/nScenarios;
    double sd = standardDeviation(payoffs);
    double r = model.riskFreeRate;
    double T = uoCallOption.maturity - model.date;

    double upperBound = exp(-r*T) * (mean - 1.96 * sd / sqrt(nScenarios));
    double lowerBound = exp(-r*T) * (mean + 1.96 * sd / sqrt(nScenarios));

    return vector<double>({upperBound,lowerBound});
}


//////////////////////////////////////
//
//   Tests
//
//////////////////////////////////////

static void testPriceCallOption() {
    rng("default");

    CallOption c;
    c.strike = 110;
    c.maturity = 2;

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    double price = pricer.price( c, m );
    double expected = c.price( m );
    ASSERT_APPROX_EQUAL( price, expected, 0.1 );
}

static void testCallDelta() {
    rng("default");

    CallOption c;
    c.strike = 110;
    c.maturity = 2;

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    double mcDelta = pricer.delta( c, m );
    double expected = c.delta( m );
    ASSERT_APPROX_EQUAL( mcDelta, expected, 0.1 );
}

static void testPricePutOption() {
    rng("default");

    PutOption p;
    p.strike = 110;
    p.maturity = 2;

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    double price = pricer.price( p, m );
    double expected = p.price( m );
    ASSERT_APPROX_EQUAL( price, expected, 0.1 );
}

static void testPutDelta() {
    rng("default");

    PutOption p;
    p.strike = 110;
    p.maturity = 2;

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    double mcDelta = pricer.delta( p, m );
    double expected = p.delta( m );
    ASSERT_APPROX_EQUAL( mcDelta, expected, 0.1 );
}

static void testPriceUpAndOutOption() {
    rng("default");

    UpAndOutOption uoc;
    uoc.strike = 110;
    uoc.maturity = 2;
    uoc.barrier = 105;

    BlackScholesModel m;
    m.volatility = 0.1;
    m.riskFreeRate = 0.05;
    m.stockPrice = 100.0;
    m.drift = 0.1;
    m.date = 1;

    MonteCarloPricer pricer;
    double price = pricer.price( uoc, m );
    
    CallOption c;
    c.strike = 110;
    c.maturity = 2;

    double expected = c.price( m );

    ASSERT( price <= expected );
}

void testMonteCarloPricer() {
    testPriceCallOption();
    testPricePutOption();
    testPriceUpAndOutOption();
    testCallDelta();
    testPutDelta();
}