#include "UpAndOutOption.h"

using namespace std;

UpAndOutOption::UpAndOutOption() :
    strike(0.0),
    maturity(0.0),
    barrier(0.0) {
}

double UpAndOutOption::payoff(vector<double> stockPrices) const{
    for (size_t i=0; i<stockPrices.size(); i++) {
        if (stockPrices[i] > barrier) {
            return 0.0;
        }
    }

    if (stockPrices.at(stockPrices.size()-1) > strike) {
        return stockPrices.at(stockPrices.size()-1) - strike;
    }

    return 0.0;
}