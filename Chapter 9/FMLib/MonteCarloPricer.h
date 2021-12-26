#pragma once

#include "stdafx.h"
#include "CallOption.h"
#include "PutOption.h"
#include "BlackScholesModel.h"

class MonteCarloPricer {
public:
    /*  Constructor */
    MonteCarloPricer();
    /*  Number of scenarios */
    int nScenarios;
    /*  Price a call option */
    double callPrice( const CallOption& option,
                  const BlackScholesModel& model );
    /*  Price a put option */
    double putPrice( const PutOption& option,
                  const BlackScholesModel& model );
};

void testMonteCarloPricer();

