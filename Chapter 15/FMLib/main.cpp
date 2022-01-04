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
#include "HedgingSimulator.h"

using namespace std;

void testPointerError() {
	// You can use this test to see what
	// happens when a null pointer exception
	// occurs
	char* s = NULL;
	*s = 'a';
}

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
	testHedgingSimulator();
	testPointerError();

    return 0;
}