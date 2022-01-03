#pragma once

#include "stdafx.h"
#include "StockPriceModel.h"
#include "PathIndependentOption.h"

class CallOption : public PathIndependentOption {
public:
    using PathIndependentOption::payoff;
    double payoff( double stockAtMaturity ) const;

    double price( const StockPriceModel& bsm )
        const;

	double delta(const StockPriceModel& bsm)
		const;

    bool isPathDependent() const {
        return false;
    }
};

void testCallOption();