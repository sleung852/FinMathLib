#ifndef F9865D2D_CCA4_4EB3_978E_13F8811DEF26
#define F9865D2D_CCA4_4EB3_978E_13F8811DEF26

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "ContinuousTimeOptionBase.h"


double impliedVolatility(
    std::shared_ptr<ContinuousTimeOptionBase> option, BlackScholesModel model,
    double price, double threshold=0.01, double maxVol=2.0);

void testImpliedVolatility();


#endif /* F9865D2D_CCA4_4EB3_978E_13F8811DEF26 */
