#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class PutOption : public PathIndependentOption {
    public:
        using PathIndependentOption::payoff;
        double payoff( double endStockPrice ) const;
        double price( const BlackScholesModel& bsm ) const;
};

void testPutOption();