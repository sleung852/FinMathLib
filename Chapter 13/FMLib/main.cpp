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
#include "UpAndOutOption.h"
#include "DownAndOutOption.h"
#include "Portfolio.h"
#include "DigitalCallOption.h"
#include "DigitalPutOption.h"
#include "RectangleRulePricer.h"

using namespace std;

int main() {

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
    testUpAndOutOption();
    testDownAndOutOption();
    testContinuousTimeOptionBase();
    testPortfolio();
	testDigitalCallOption();
	testDigitalPutOption();
	testRectangleRulePricer();
    return 0;
}