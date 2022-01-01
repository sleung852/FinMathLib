#pragma once

#include "PathIndependentOption.h"

class DigitalCallOption : public PathIndependentOption {

	double payoff(double stockAtMaturity) const {
		if (stockAtMaturity > getStrike()) {
			return 1.0;
		}
		else {
			return 0.0;
		}
	}

};


void testDigitalCallOption();