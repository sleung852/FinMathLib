#pragma once

#include "stdafx.h"

/**
 *   This states that all path independent options
 *   have a payoff determined by the final stock price
 */
class ContinuousTimeOption {
public:
    /*  A virtual destructor */
    virtual ~ContinuousTimeOption() {}
    /*  Returns the payoff at maturity */
    virtual double payoff(
	    const std::vector<double>& stockPath) const = 0;
    /*  Returns the maturity of the option */
    virtual double getMaturity() const
        = 0;
};