#ifndef AB8623DC_05E7_439F_8713_2C6C78B8093B
#define AB8623DC_05E7_439F_8713_2C6C78B8093B

#include "stdafx.h"
#include "AsianOption.h"

class AsianCallOption : public AsianOption {
    public:
        Matrix payoff(const Matrix&prices) const override;
};

void testAsianCallOption();

#endif /* AB8623DC_05E7_439F_8713_2C6C78B8093B */
