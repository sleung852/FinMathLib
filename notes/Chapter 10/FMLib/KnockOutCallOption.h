#ifndef D3037E52_99C6_44F4_B28B_E8A5359D2D8A
#define D3037E52_99C6_44F4_B28B_E8A5359D2D8A

#include "stdafx.h"
#include "ContinuousTimeOption.h"

class KnockOutCallOption : public ContinuousTimeOption {
    public:
        KnockOutCallOption();
        KnockOutCallOption(double strike, double maturity, double barrier);

        double strike;
        double maturity;
        double barrier;

        double payoff(const std::vector<double>& stockPrices) const;
        double getMaturity() const;

};

#endif /* D3037E52_99C6_44F4_B28B_E8A5359D2D8A */
