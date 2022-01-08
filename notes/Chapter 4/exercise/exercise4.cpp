#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace std;

// 4.8.1
int factorialWhileLoop(int n) {
    if (n < 0) throw("n must be greater or equal to 0");
    if (n == 0) return 1;
    int factorial = 1;
    int count = 1;
    while (n >= count) {
        factorial *= count;
        count++;
    }
    return factorial;
}

int factorialForLoop(int n) {
    if (n < 0) throw("n must be greater or equal to 0");
    if (n == 0) return 1;
    int factorial = 1;
    for (int i=1; i<=n; i++) {
        factorial *= i;
    }
    return factorial;
}

int factorialDoWhileLoop(int n) {
    if (n < 0) throw("n must be greater or equal to 0");
    if (n == 0) return 1;
    int factorial = 1;
    int count = 1;
    do {
        factorial *= count;
        count++;
    } while (n >= count);
    return factorial;
}

// 4.8.2
double rectangleApproximation(double (*funct)(double), double a, double b, int n) {
    double h = (b-a)/n;
    double approx = 0;
    for (int i=0; i<n-1; i++) {
        approx += funct(a + i*h + h/2);
    }
    return approx/n;
}

// 4.8.3
double function1(double t) {
    return exp(-t*t/2);
}

double function2(double x, double s) {
    return exp(-pow(x+1-1/s,2)/2)/(s*s);
}

// 4.8.4
int fibonnaciLoop(int x){
    if (x == 0) return 0;
    if (x == 1) return 1;
    int n = 1;
    int last = 0; // F(0)
    int current = 1; // F(1)
    int temp;
    while (n < x) {
        temp = last + current;
        last = current;
        current = temp;
        n++;
    }
    return current;
}

// 4.8.5 & 4.8.6

// from 3.9.5
const double PI = 3.141592653589793;
double SQRT2PI = sqrt(2*PI);
double computek2(double x) {
    return 1/(1+0.2316419*x);
}
// from 3.9.6
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
    double k = computek2(x);
    return 1 - (1/SQRT2PI) * exp(-pow(x,2.0)/2) * hornerFunction(k, 0.0, 0.319381530, -0.356563782, 1.781477937, -1.821255978, 1.330274429);
}

double computeNormalCDF3(double x) {
    if (x < 0) return 1 - approximateNormalCDF3(-x);
    else return approximateNormalCDF3(x);
}
// from 3.9.7 - estimate with Moro algorithm
double norminv(double x, bool err_check) {
    // if (x < 0 || x > 1) throw("x must be between 0 and 1!"); // 4.8.5
    if (err_check && (x < 0 || x > 1)) throw("x must be between 0 and 1!"); // 4.8.6
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
    double r, y, s, t;
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

// 4.8.7
void printRange(int a=0, int b=9) {
    for (int i=a; i<=b; i++) cout << i << " ";
    cout << endl;
}

int main() {

    // 4.8.1
    cout << "Exercise 4.8.1\n";
    cout << "Factorial of 10:\n";
    int x = 10;
    cout << "While Loop:\n";
    cout << factorialWhileLoop(x) << endl;
    cout << "For Loop:\n";
    cout << factorialForLoop(x) << endl;
    cout << "Do-While Loop:\n";
    cout << factorialDoWhileLoop(x) << endl;
    cout << endl;

    // 4.8.2
    cout << "Exercise 4.8.2\n";
    cout << "Approximate integral of sin(x) with a=0.5, b=3 with n=10:\n";
    cout << rectangleApproximation(sin, 0.5, 3, 10) << endl;
    cout << "Approximate integral of sin(x) with a=0.5, b=3 with n=50:\n";
    cout << rectangleApproximation(sin, 0.5, 3, 50) << endl;
    cout << endl;

    // 4.8.3
    cout << "Exercise 4.8.3\n";
    // ?
    cout << endl;

    // 4.8.4
    cout << "Exercise 4.8.4\n";
    cout << "Fibonacci(10): " << fibonnaciLoop(10) << endl;
    cout << endl;

    // 4.8.5 & 4.8.6
    cout << "Exercise 4.8.5 & 4.8.6\n";
    cout << "Boolean set to false - no error if out of range:\n";
    cout << "norminv(-0.1): " << norminv(-0.1, false) << endl;
    cout << "norminv(0.37): " << norminv(0.37, false) << endl;
    cout << "norminv(1.2): " << norminv(1.2, false) << endl;
    cout << "Boolean set to true - throw error if out of range:\n";
    // cout << "norminv(-0.1): " << norminv(-0.1, true) << endl;
    cout << "norminv(0.37): " << norminv(0.37, false) << endl;
    // cout << "norminv(1.2): " << norminv(1.2, true) << endl;
    cout << endl;

    // 4.8.7
    cout << "Exercise 4.8.7\n";
    printRange();

}