#pragma once

#include "stdafx.h"
#include "ContinuousTimeOption.h"
#include "StockPriceModel.h"

class MonteCarloPricer {
public:
    /*  Constructor */
    MonteCarloPricer();
    /*  Number of scenarios */
    int nScenarios;
    /*  The number of steps in the calculation */
    int nSteps;
    /*  Price the option */
    double price( const ContinuousTimeOption& option,
                  const StockPriceModel& model );

    double delta( const ContinuousTimeOption& option,
                  StockPriceModel model,
                  double h);

};

void testMonteCarloPricer();

