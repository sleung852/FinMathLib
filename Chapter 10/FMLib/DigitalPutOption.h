#ifndef B0C311A9_DEB5_470F_B49F_28BCCE6585D4
#define B0C311A9_DEB5_470F_B49F_28BCCE6585D4

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class DigitalPutOption : public PathIndependentOption {
    public:
        DigitalPutOption();
        double strike;
        double maturity;

        double payoff( double stockAtMaturity ) const;

        // double price( const BlackScholesModel& bsm )
        //     const;

        double getMaturity() const;
};

void testDigitalPutOption();

#endif /* B0C311A9_DEB5_470F_B49F_28BCCE6585D4 */
