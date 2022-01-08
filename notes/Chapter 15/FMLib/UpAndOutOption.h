#pragma once

#include "KnockoutOption.h"

class UpAndOutOption : public KnockoutOption {
public:
    double payoff(
        const std::vector<double>& prices ) const;
};


void testUpAndOutOption();