#include "matlib.h"
#include "geometry.h"
#include "charts.h"
#include "usageExamples.h"
#include "options.h"

using namespace std;

int main() {
    testMatlib();
    testGeometry();
    testCharts();
    testUsageExamples();

    // 7.7.8
    double volatility = 0.2;
    double strike = 100;
    double time = 1.0;
    double rate = 0.05;

    vector<double> spots({90, 95, 100, 105, 110, 115, 120, 125});
    vector<double> option_prices(spots.size());
    for (int i=0; i<spots.size(); i++) {
        option_prices[i] = blackScholesCallPrice(strike, time, spots.at(i), volatility, rate);
    }
    lineChart("blackscholes.html", spots, option_prices, "Spot", "Option Price");

    

}