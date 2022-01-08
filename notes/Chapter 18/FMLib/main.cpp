#include "matlib.h"
#include "geometry.h"
#include "textfunctions.h"
#include "CallOption.h"
#include "PutOption.h"
#include "PieChart.h"
#include "LineChart.h"
#include "BlackScholesModel.h"
#include "MultiStockModel.h"
#include "Histogram.h"
#include "MonteCarloPricer.h"
#include "UpAndOutOption.h"
#include "DownAndOutOption.h"
#include "Portfolio.h"
#include "Matrix.h"
#include "Fibonacci.h"
#include "BasketOfOptions.h"
#include "HashMap.h"

using namespace std;

// 18.12.4
template <typename T, typename Container>
T mapGet(const Container& container, T key) {
    auto it = container.begin();
    while (it != container.end()) {
        if (it->first == key) {
            return it->second;
        }
        it++;
    }
    throw("key is not found");
    T out;
    return out;
}

int main() {

    testMatrix();
    testMatlib();
    testMultiStockModel();
	testBlackScholesModel();
	testGeometry();
    testPieChart();
    testCallOption();
    testPutOption();
    testLineChart();
    testTextFunctions();
    testHistogram();
    testMonteCarloPricer();
    testDownAndOutOption();
    testContinuousTimeOptionBase();
    testPortfolio();
    testPutOption();
    testUpAndOutOption();

    testFibonacciNumberSpeed();
    testBasketOfOptions();

    testHashMap();

    std::map<int, int> mapExample;
    mapExample[1] = 1;
    mapExample[2] = 2;

    std::cout << "GetOne: " << mapGet(mapExample, 1) << std::endl;
    std::cout << "GetTwo: " << mapGet(mapExample, 2) << std::endl;
    // std::cout << "GetThree: " << mapGet(mapExample, 3) << std::endl; //expected error

    return 0;
}