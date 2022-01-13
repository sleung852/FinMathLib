#pragma once

#include "PathIndependentOption.h"

class DigitalCallOption : public PathIndependentOption {
	public:

    Matrix payoffAtMaturity( const Matrix& stockAtMaturity ) const;

};


void testDigitalCallOption();