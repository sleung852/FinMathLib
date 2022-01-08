#include "Stock.h"

double Stock::price(const BlackScholesModel& model) const {
    return model.stockPrice;
}