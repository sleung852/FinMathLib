#ifndef BAC1B2B5_D044_455D_9070_62A1926DCF02
#define BAC1B2B5_D044_455D_9070_62A1926DCF02

#include "stdafx.h"

class UpAndOutOption {
public:
    UpAndOutOption();
    double strike;
    double maturity;
    double barrier;

    double payoff( std::vector<double> stockPrices ) const;

};

#endif /* BAC1B2B5_D044_455D_9070_62A1926DCF02 */
