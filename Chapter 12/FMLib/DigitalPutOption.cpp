#include "DigitalPutOption.h"

double DigitalPutOption::payoff(double endStockPrice) const {
    if (endStockPrice < getStrike()) {
        return 1.0;
    } else {
        return 0.0;
    }
}
