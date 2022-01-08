#include "NormalPDF.h"
#include "geometry.h" // for PI
#include "matlib.h"

using namespace std;

NormPDF::NormPDF() :
    mu(0.0), sigma(1.0){
}


NormPDF::NormPDF(double mu_in, double sigma_in) :
    mu(mu_in), sigma(sigma_in){
}


double NormPDF::evaluate(double x) {
    return exp(-0.5*pow((x-mu)/sigma,2.0))/(sigma*sqrt(2*PI));
}

static void testNormPDFIntegral() {
    NormPDF normpdf;
    double integralResult = integral(normpdf, -1.96, 1.96, 1000);
    stringstream ss;
    ss << "Result for 10.6.2\n";
    ss << "Integral of NormPDF -1.96 and 1.96: " << integralResult << "\n";
    DEBUG_PRINT(ss.str());
    ASSERT_APPROX_EQUAL(integralResult, 0.95, 0.01);
}

void testNormPDF() {
    TEST ( testNormPDFIntegral );
}