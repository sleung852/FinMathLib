#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class CallOption : public PathIndependentOption {
public:
    /*  Returns the payoff at maturity given a column vector
        of scenarios */
    Matrix payoffAtMaturity( const Matrix& stockAtMaturity ) const;

    double price( const BlackScholesModel& bsm )
        const;

    std::string optionName = std::string("Call Option");
    
};

std::ostream& operator<<(std::ostream& os, const CallOption& callOption );

void testCallOption();

