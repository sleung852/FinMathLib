#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"

class CallOption {
public:
    CallOption();
    double strike;
    double maturity;

	double payoff(double stockAtMaturity) const {
		if (stockAtMaturity>strike) {
			return stockAtMaturity - strike;
		}
		else {
			return 0.0;
		}
	}

    double price( const BlackScholesModel& bsm )
        const;
};
