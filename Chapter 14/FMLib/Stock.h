#pragma once

#include "Priceable.h"

class Stock : public Priceable {
public:
	virtual ~Stock(){};
	/*  Compute the price of the security in the
	Black Scholes world */
	virtual double price(
		const StockPriceModel& model) const {
		return model.getStockPrice();
	}
};