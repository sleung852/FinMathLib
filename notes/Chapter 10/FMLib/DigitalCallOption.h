#ifndef A60B91E7_03C0_48DC_9058_05C56C306E5A
#define A60B91E7_03C0_48DC_9058_05C56C306E5A

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "PathIndependentOption.h"

class DigitalCallOption : public PathIndependentOption {
    public:
        DigitalCallOption();
        double strike;
        double maturity;

        double payoff( double stockAtMaturity ) const;

        // double price( const BlackScholesModel& bsm )
        //     const;

        double getMaturity() const;
};

void testDigitalCallOption();

#endif /* A60B91E7_03C0_48DC_9058_05C56C306E5A */
