#pragma once

#include "Priceable.h"
#include "StockPriceModel.h"

class ZeroCouponBond : public Priceable {
public:
	virtual ~ZeroCouponBond(){};
	double maturity;
	/*  Compute the price of the security in the
		Black Scholes world */
	virtual double price(
		const StockPriceModel& model) const {
		return exp(-model.getRiskFreeRate()*maturity);
	}
};