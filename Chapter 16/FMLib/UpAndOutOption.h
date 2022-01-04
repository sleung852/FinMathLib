#pragma once

#include "KnockoutOption.h"

class UpAndOutOption : public KnockoutOption {
public:
    Matrix payoff(
        const Matrix& prices ) const;

    std::string optionName = std::string("Up And Out Option");
};

std::ostream& operator<<(std::ostream& os, const UpAndOutOption& upAndOutOption );

void testUpAndOutOption();