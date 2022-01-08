#pragma once

#include "KnockoutOption.h"

class DownAndOutOption : public KnockoutOption {
public:
    Matrix payoff(
        const Matrix& prices ) const;

    std::string optionName = std::string("Down And Out Option");

};

std::ostream& operator<<(std::ostream& os, const DownAndOutOption& downAndOutOption );

void testDownAndOutOption();