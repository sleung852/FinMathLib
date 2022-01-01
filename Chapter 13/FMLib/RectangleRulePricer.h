#pragma once

#include "PathIndependentOption.h"
#include "BlackScholesModel.h"


class RectangleRulePricer {
public:
	int nSteps;
	double price(const PathIndependentOption& option,
				 const BlackScholesModel& model);

	RectangleRulePricer() : nSteps(1000) {}
};


void testRectangleRulePricer();