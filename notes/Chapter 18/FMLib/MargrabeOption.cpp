#include "MargrabeOption.h"
#include "MonteCarloPricer.h"

using namespace std;

Matrix MargrabeOption::payoff(const MarketSimulation& simulation) const {
    SPCMatrix allStock1PricePathPtr = (simulation.getStockPaths(stock1));
    // get last step of all path
    Matrix finalStock1Prices = allStock1PricePathPtr->col(allStock1PricePathPtr->nCols()-1 );

    SPCMatrix allStock2PricePathPtr = (simulation.getStockPaths(stock1));
    Matrix finalStock2Prices = allStock2PricePathPtr->col(allStock2PricePathPtr->nCols()-1 );

    Matrix payoff = finalStock1Prices - finalStock2Prices;
    Matrix mask(payoff.nRows(), payoff.nCols());
    // check if payoff greater than zero
    mask = payoff > mask;

    payoff.times(mask);
    return payoff;
}

double MargrabeOption::price(const MultiStockModel& model) const {
    MonteCarloPricer pricer;
    return pricer.price( *this, model);
}