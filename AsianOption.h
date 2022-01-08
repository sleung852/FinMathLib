#pragma once

#include "ContinuousTimeOptionBase.h"

/**
 *  This class represents an Asian call option
 */
class AsianOption : public ContinuousTimeOptionBase {
public:
	virtual Matrix payoff( const Matrix&prices) const=0;

	bool isPathDependent() const {
		return true;
	}

};

// void testAsianOption();