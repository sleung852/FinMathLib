#include "matlib.h"
#include "geometry.h"
#include "options.h"

using namespace std;


int main() {
    testMatlib();

    // 6.6.1 & 6.6.2
    cout << "Exercise 6.6.1\n";
    testGeometric();

    // 6.6.3
    // because the individual unit test function do not
    // need to be accessed by other users. Only the testMatlib is needed.

    // 6.6.4
    // see options.h & options.cpp
    cout << "Exercise 6.6.4\n";
    testOptions();
}