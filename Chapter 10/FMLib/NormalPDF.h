#ifndef C87045A8_56CA_4F65_8D10_B8F016BD029B
#define C87045A8_56CA_4F65_8D10_B8F016BD029B

#include "stdafx.h"
#include "RealFunction.h"

class NormPDF : public RealFunction {
    public:
        NormPDF(double mu, double sigma);
        NormPDF();
        double mu;
        double sigma;

        double evaluate(double x);
};

void testNormPDF();

#endif /* C87045A8_56CA_4F65_8D10_B8F016BD029B */
