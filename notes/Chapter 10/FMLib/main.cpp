#include "matlib.h"
#include "geometry.h"
#include "textfunctions.h"
#include "CallOption.h"
#include "PutOption.h"
#include "PieChart.h"
#include "LineChart.h"
#include "BlackScholesModel.h"
#include "Histogram.h"
#include "MonteCarloPricer.h"
#include "NormalPDF.h"
#include "RectangleRulePricer.h"

using namespace std;


int main() {
    // test functions
    testMatlib();
    testGeometry();
    testPieChart();
    testCallOption();
    testPutOption();
    testBlackScholesModel();
    testLineChart();
    testTextFunctions();
    testHistogram();
    testMonteCarloPricer();
    testNormPDF();
    testRectangleRulePricer();
    return 0;
}