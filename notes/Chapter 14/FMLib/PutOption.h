#pragma once

#include "stdafx.h"
#include "StockPriceModel.h"
#include "PathIndependentOption.h"

class PutOption : public PathIndependentOption {
public:

    /*  Calculate the payoff of the option given
        a history of prices */
    using PathIndependentOption::payoff;
    double payoff( double stockAtMaturity ) const;

    double price( const StockPriceModel& bsm )
        const;

	double delta( const StockPriceModel& bsm )
		const;

    bool isPathDependent() const {
        return false;
    };
};

void testPutOption();