#include "matlib.h"
#include "geometry.h"
#include "CallOption.h"
#include "PutOption.h"
#include "PieChart.h"
#include "LineChart.h"
#include "BlackScholesModel.h"

using namespace std;

int main() {
    testMatlib();
    testGeometry();
    testPieChart();
    // 8.6.2
    testLineChart();
    testCallOption();
    // 8.6.1
    testPutOption();
    testBlackScholesModel();
}