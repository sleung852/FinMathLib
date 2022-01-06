#include "BasketOfOptions.h"
#include "MonteCarloPricer.h"
#include "Portfolio.h"
#include "UpAndOutOption.h"
#include "testing.h"

using namespace std;

BasketOfOptions::BasketOfOptions(
    vector<shared_ptr<ContinuousTimeOption> > options,
    vector<double> weights,
    double maturity,
    set<string> dependentStocks) :
    options(options), weights(weights), maturity(maturity), stocks(dependentStocks) {
        DEBUG_PRINT("BasketOfOptions instance created");
    }

Matrix BasketOfOptions::payoff(const MarketSimulation &simulation) const {
    vector<Matrix> payoffs;
    for (int i=0; i< options.size(); i++) {
        stringstream sslog;
        sslog << "Individual Payoff Matrix:\n" << options[i]->payoff(simulation);
        DEBUG_PRINT(sslog.str());
        payoffs.push_back(options[i]->payoff(simulation) * weights[i]);
    }

    Matrix basketPayoffs(payoffs[0].nRows(), payoffs[0].nCols());
    for (auto payoff: payoffs) {
        basketPayoffs += payoff;
    }

    DEBUG_PRINT("BasketOfOptions Payoff computed");
    stringstream sslog;
    sslog << "Aggregate Payoff Matrix:\n" << basketPayoffs;
    DEBUG_PRINT(sslog.str());
    return basketPayoffs;
}

double BasketOfOptions::price(const MultiStockModel& model) const {
    MonteCarloPricer pricer;
    DEBUG_PRINT("BasketOfOptions Price computed");
    return pricer.price( *this, model);
}


// static void testBasketOfOptions1() {
// 	auto model = MultiStockModel::createTestModel();
// 	// auto p = Portfolio::newInstance();
// 	auto stocks = model.getStocks();

// 	double q0 = 1.0;
// 	auto stock0 = stocks[0];
// 	SPUpAndOutOption o0=make_shared<UpAndOutOption>();
// 	o0->setStock(stock0);
// 	o0->setStrike(model.getStockPrice(stock0));
// 	o0->setBarrier(2*model.getStockPrice(stock0));
//     o0->setMaturity(3);
// 	// p->add(q0, o0);
	
// 	double q1 = 2.0;
// 	auto stock1 = stocks[1];
// 	SPUpAndOutOption o1=make_shared<UpAndOutOption>();
// 	o1->setStock(stock1);
// 	o1->setStrike(model.getStockPrice(stock1));
// 	o1->setBarrier(2 * model.getStockPrice(stock1));
//     o1->setMaturity(3);
// 	// p->add(q1, o1);

//     vector<shared_ptr<ContinuousTimeOption> > optionsPtr({o0, o1});
//     vector<double> weights({q0, q1});
//     set<string> uniqueStocks({stock0, stock1});
//     BasketOfOptions basketOfOptions(optionsPtr, weights, 3, uniqueStocks);

//     double price = basketOfOptions.price(model);
//     stringstream ss;
//     ss << "basket of options price: " << price;
//     DEBUG_PRINT(ss.str());

// }

void testBasketOfOptions() {
    setDebugEnabled(true);
    // TEST (testBasketOfOptions1);
    setDebugEnabled(false);
}