#include "KnockOutCallOption.h"

double KnockOutCallOption::payoff(const std::vector<double>& stockPrices) const {
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


double KnockOutCallOption::getMaturity() const {
    return maturity;
}

KnockOutCallOption::KnockOutCallOption(double strike, double maturity, double barrier) : 
    strike(strike), maturity(maturity), barrier(barrier) {}

KnockOutCallOption::KnockOutCallOption() : 
    strike(0.0), maturity(0.0), barrier(0.0) {}