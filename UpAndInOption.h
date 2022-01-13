#pragma once

#include "KnockoutOption.h"

class UpAndInOption : public KnockoutOption {
public:
    Matrix payoff(
        const Matrix& prices ) const;
};

typedef std::shared_ptr<UpAndInOption> SPUpAndInOption;
typedef std::shared_ptr<const UpAndInOption> SPCUpAndInOption;

void testUpAndInOption();