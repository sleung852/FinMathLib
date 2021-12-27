#pragma once

#include "stdafx.h"
#include "CallOption.h"
#include "PutOption.h"
#include "UpAndOutOption.h"
#include "BlackScholesModel.h"

class MonteCarloPricer {
public:
    /*  Constructor */
    MonteCarloPricer();
    /*  Number of scenarios */
    int nScenarios;
    /* Compute Option Prices */
    /*  Price a call option */
    double price( const CallOption& option,
                  const BlackScholesModel& model );
    /*  Price a put option */
    double price( const PutOption& option,
                  const BlackScholesModel& model );
    /*  Price a call Up and Out option */
    double price( const UpAndOutOption& option,
                  const BlackScholesModel& model );

    /*  Compute Deltas */
    double delta( const CallOption& option,
                    const BlackScholesModel& model,
                    double h=1e-6);
    double delta( const PutOption& option,
                    const BlackScholesModel& model,
                    double h=1e-6);
    double delta( const UpAndOutOption& option,
                    const BlackScholesModel& model,
                    double h=1e-6);
    // Confidence Interval
    /*  Price a call option */
    std::vector<double> confidenceInterval( const CallOption& option,
                                const BlackScholesModel& model );
    /*  Price a put option */
    std::vector<double> confidenceInterval( const PutOption& option,
                                const BlackScholesModel& model );
    /*  Price a call Up and Out option */
    std::vector<double> confidenceInterval( const UpAndOutOption& option,
                            const BlackScholesModel& model );

    /*  Price a call option with Antithetic */
    double priceAntithetic( const CallOption& option,
                            const BlackScholesModel& model );

};

void testMonteCarloPricer();

