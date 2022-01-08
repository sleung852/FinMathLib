#include <iostream>

using namespace std;

#define MAX(a,b) (((a) > (b)) ? (a) : (b))

int main() {

    // 1. Testing how to use macros
    int v_a = 30;
    int v_b = 20;
    cout << MAX(v_a, v_b) << endl; // essentially, the compiler will automatically substitute in the function

    return 0;
}