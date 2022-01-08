#ifndef F0B37E1A_8B98_421E_9A23_795CBCC370C4
#define F0B37E1A_8B98_421E_9A23_795CBCC370C4

#include "stdafx.h"
#include "AsianOption.h"

class AsianPutOption : public AsianOption {
    public:
        Matrix payoff(const Matrix&prices) const override;
};

void testAsianPutOption();

#endif /* F0B37E1A_8B98_421E_9A23_795CBCC370C4 */
