#pragma once

#include "PathIndependentOption.h"


class DigitalPutOption : public PathIndependentOption {

	Matrix payoffAtMaturity( const Matrix& stockAtMaturity ) const;


};


void testDigitalPutOption();