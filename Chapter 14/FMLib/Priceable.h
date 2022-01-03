#pragma once

#include "StockPriceModel.h"

/**
 *   Represents a general security
 */
class Priceable {
public:
    /*  Compute the price of the security in the
        Black Scholes world */
    virtual double price(
        const StockPriceModel& model ) const = 0;
};