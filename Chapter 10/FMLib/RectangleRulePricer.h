#ifndef BD3A68B7_C476_4623_B977_6D94313417D8
#define BD3A68B7_C476_4623_B977_6D94313417D8

#include "BlackScholesModel.h"
#include "stdafx.h"
#include "PathIndependentOption.h"

class RectangleRulePricer {
    public:
        double price(const PathIndependentOption& option, const BlackScholesModel& bsm) const;

};

void testRectangleRulePricer();

#endif /* BD3A68B7_C476_4623_B977_6D94313417D8 */
