#pragma once

#include "PathIndependentOption.h"


class DigitalPutOption : public PathIndependentOption {

	double payoff(double stockAtMaturity) const {
		if (stockAtMaturity > getStrike()) {
			return 0.0;
		}
		else {
			return 1.0;
		}
	}

};


void testDigitalPutOption();