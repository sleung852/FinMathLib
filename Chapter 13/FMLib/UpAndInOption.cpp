#include "UpAndInOption.h"

double UpAndInOption::payoff(const std::vector<double> &stockPrices) const {
    bool flag = false;
    for (size_t i=0; i<stockPrices.size(); i++) {
        if (stockPrices.at(i) >= getBarrier()) {
            flag = true;
            break;
        }
    }
    if (flag && stockPrices.back() > getStrike()) {
        return stockPrices.back() - getStrike();
    }
    return 0.0;
}