#ifndef C6ED638A_DC5F_44EF_92D9_2CD54726E7EE
#define C6ED638A_DC5F_44EF_92D9_2CD54726E7EE

#include "stdafx.h"
#include "matlib.h"

double blackScholesPutPrice(double strike, double t, double spot, double volatility, double riskfreerate);
double blackScholesCallPrice(double strike, double t, double spot, double volatility, double riskfreerate);

void testOptions();

#endif /* C6ED638A_DC5F_44EF_92D9_2CD54726E7EE */
