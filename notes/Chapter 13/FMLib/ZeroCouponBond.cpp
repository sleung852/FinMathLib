#include "ZeroCouponBond.h"

double ZeroCouponBond::price(const BlackScholesModel& model) const {
    double deltaT = expiry - model.date;
    return exp(-model.riskFreeRate*deltaT);
}