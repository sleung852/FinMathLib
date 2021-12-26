#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"

class PutOption {
public:
    double strike;
    double maturity;

    PutOption();
    PutOption(double strike, double maturity);
    double payoff( double stockAtMaturity ) const;
    double price( const BlackScholesModel& bsm )
        const;
};

void testPutOption();