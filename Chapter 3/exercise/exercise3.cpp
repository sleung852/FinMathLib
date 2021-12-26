#include <iostream>
#include <cmath>

using namespace std;

// 3.9.1
int recursiveSum(int n) {
    if (n==1) return 1;
    return n + recursiveSum(n-1);
}

// 3.9.2
void recursivePrintRange(int a, int b) {
    if (a > b) {
        cout << endl;
        return;
    }
    cout << a << " ";
    return recursivePrintRange(a+1, b);
}

// 3.9.3
int fibonacciNumber(int n) {
    // cout << "Executed!" << endl;
    if (n==0) return 1;
    if (n==1) return 1;
    return fibonacciNumber(n-1) + fibonacciNumber(n-2);
}

// 3.9.4
double computek(double x) {
    return 1/(1+0.2316419*x);
}

double approximateNormalCDF(double x) {
    const double PI = 3.141592653589793;
    double k = computek(x);
    return 1 - (1/sqrt(2*PI)) * exp(-pow(x,2.0)/2) * k * (0.319381530 + k * (-0.356563782 + k * (1.781477937) + k * (-1.821255978 + 1.330274429*k)));
}

double computeNormalCDF(double x) {
    if (x < 0) return 1 - approximateNormalCDF(-x);
    else return approximateNormalCDF(x);
}

// 3.9.5
const double PI = 3.141592653589793;
double SQRT2PI = sqrt(2*PI);
double computek2(double x) {
    return 1/(1+0.2316419*x);
}

double approximateNormalCDF2(double x) {
    double k = computek(x);
    return 1 - (1/SQRT2PI) * exp(-pow(x,2.0)/2) * k * (0.319381530 + k * (-0.356563782 + k * (1.781477937) + k * (-1.821255978 + 1.330274429*k)));
}

double computeNormalCDF2(double x) {
    if (x < 0) return 1 - approximateNormalCDF2(-x);
    else return approximateNormalCDF2(x);
}

// 3.9.6
double hornerFunction(double x, double a0) {
    return a0;
}
double hornerFunction(double x, double a0, double a1) {
    return a0 + x*hornerFunction(x, a1);
}
double hornerFunction(double x, double a0, double a1, double a2) {
    return a0 + x*hornerFunction(x, a1, a2);
}
double hornerFunction(double x, double a0, double a1, double a2, double a3) {
    return a0 + x*hornerFunction(x, a1, a2, a3);
}
double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4) {
    return a0 + x*hornerFunction(x, a1, a2, a3, a4);
}
double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4, double a5) {
    return a0 + x*hornerFunction(x, a1, a2, a3, a4, a5);
}
double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4, double a5, double a6) {
    return a0 + x*hornerFunction(x, a1, a2, a3, a4, a5, a6);
}
double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7) {
    return a0 + x*hornerFunction(x, a1, a2, a3, a4, a5, a6, a7);
}
double hornerFunction(double x, double a0, double a1, double a2, double a3, double a4, double a5, double a6, double a7, double a8) {
    return a0 + x*hornerFunction(x, a1, a2, a3, a4, a5, a6, a7, a8);
}

double approximateNormalCDF3(double x) {
    double k = computek(x);
    return 1 - (1/SQRT2PI) * exp(-pow(x,2.0)/2) * hornerFunction(k, 0.0, 0.319381530, -0.356563782, 1.781477937, -1.821255978, 1.330274429);
}

double computeNormalCDF3(double x) {
    if (x < 0) return 1 - approximateNormalCDF3(-x);
    else return approximateNormalCDF3(x);
}

// 3.9.7 - estimate with Moro algorithm
double norminv(double x) {    
    // define constants
    const double a0 = 2.50662823884;
    const double a1 = -18.61500062529;
    const double a2 = 41.39119773534;
    const double a3 = -25.44106049637;
    const double b1 = -8.47351093090;
    const double b2 = 23.08336743743;
    const double b3 = -21.06224101826;
    const double b4 = 3.13082909833;
    const double c0 = 0.3374754822726147;
    const double c1 = 0.9761690190917186;
    const double c2 = 0.1607979714918209;
    const double c3 = 0.0276438810333863;
    const double c4 = 0.0038405729373609;
    const double c5 = 0.0003951896511919;
    const double c6 = 0.0000321767881768;
    const double c7 = 0.0000002888167364;
    const double c8 = 0.0000003960315187;
    // declare
    double r, y, s, t;
    // compute variables
    y = x - 0.5;
    if (abs(y) < 0.42) {
        r = pow(y,2.0);
        return y * hornerFunction(r, a0, a1, a2, a3) / hornerFunction(r, 1.0, b1, b2, b3, b4);
    } else {
        if (y < 0) r = x;
        else r = 1.0-x;
        s = log(-log(r));
        t = hornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
        if (x > 0.5) return t;
        else return -t;
    }
}

// 3.9.8

double blackScholesCallPrice(double strike, double t, double spot, double volatility, double riskfreerate) {
    double d1 = (log(spot/strike) + (riskfreerate + pow(volatility, 2.0)/2) * t) / (volatility * sqrt(t));
    double d2 = d1 - volatility * sqrt(t);
    return computeNormalCDF3(d1) * spot - computeNormalCDF3(d2) * strike * exp(-riskfreerate * t);
}

// 3.9.11

double approximateNormalCDF4(double x) {
    double k = computek(x);
    return erfc(x) * hornerFunction(k, 0.0, 0.319381530, -0.356563782, 1.781477937, -1.821255978, 1.330274429);
}

double computeNormalCDF4(double x) {
    if (x < 0) return 1 - approximateNormalCDF4(-x);
    else return approximateNormalCDF4(x);
}

int main() {
    // 3.9.1
    cout << "Exercise 3.9.1\n";
    int x = 32;
    cout << "Recursive Sum of " << x << ": " << recursiveSum(32) << endl;
    cout << "which should equal to " << x*(x+1)/2 << endl;
    cout << endl;

    // 3.9.2
    cout << "Exercise 3.9.2\n";
    int a, b;
    a = 3;
    b = 10;
    cout << "Print range between " << a << " and " << b << ": " << endl;
    recursivePrintRange(a, b);
    cout << endl;

    // 3.9.3
    cout << "Exercise 3.9.3\n";
    x = 5;
    cout << "Fibonacci number at " << x << ": " << fibonacciNumber(x) << endl;
    cout << endl;

    // 3.9.4
    cout << "Exercise 3.9.4\n";
    double x1 = 1.96;
    double x2 = -1.96;
    cout << "Normal CDF with x=" << x1 << ": " << computeNormalCDF(x1) << endl;
    cout << "Normal CDF with x=" << x2 << ": " << computeNormalCDF(x2) << endl;
    cout << endl;

    // 3.9.5
    cout << "Exercise 3.9.5\n";
    cout << "Normal CDF with x=" << x1 << ": " << computeNormalCDF2(x1) << endl;
    cout << "Normal CDF with x=" << x2 << ": " << computeNormalCDF2(x2) << endl;
    cout << endl;

    // 3.9.6
    cout << "Exercise 3.9.6\n";
    cout << "Normal CDF with x=" << x1 << ": " << computeNormalCDF3(x1) << endl;
    cout << "Normal CDF with x=" << x2 << ": " << computeNormalCDF3(x2) << endl;
    cout << endl;

    // 3.9.7
    cout << "Exercise 3.9.7\n";
    x1 = computeNormalCDF3(x1);
    x2 = computeNormalCDF3(x2);
    cout << "Norm Cum Inverse with x=" << x1 << ": " << norminv(x1) << endl;
    cout << "Norm Cum Inverse x=" << x2 << ": " << norminv(x2) << endl;
    cout << endl;

    // 3.9.8
    cout << "Exercise 3.9.8\n";
    cout << "Call price is: " << blackScholesCallPrice(100, 0.5, 110, 0.1, 0.03) << endl;

    // 3.9.9
    /*
    No. Easier to scale.
    */

    // 3.9.10
    /*
    CumNormCDF: http://statisticshelper.com/normal-distribution-calculator
    InverseCDF: https://onlinestatbook.com/2/calculators/inverse_normal_dist.html
    Black Scholes: https://goodcalculators.com/black-scholes-calculator/

    Of course, you can also put a random value via the CumNormCDF and invert the output with InverseCDF to see whether
    the random value is returned
    */

    // 3.9.11
    cout << "Exercise 3.9.11\n";
    x1 = 1.96;
    x2 = -1.96;
    cout << "Normal CDF with x=" << x1 << ": " << computeNormalCDF4(x1) << endl;
    cout << "Normal CDF with x=" << x2 << ": " << computeNormalCDF4(x2) << endl;
    cout << endl;
}