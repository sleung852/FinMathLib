#include "geometry.h"
#include <iostream>

using namespace std;

int main() {

    // 5.5.1
    cout << "Exercise 5.5.1\n";
    double r=3;
    cout << "Circumference: " << calculateCircumference(r) << endl;
    cout << "Area: " << calculateCircleArea(r) << endl;
    // No, static function should only be used if they are not in the header file
    // implying that the functions/declarations are not expected to be used be
    // external parties
    cout << endl;

    // 5.5.2
    // matlib.h because it provides all the necessary information.

    // 5.5.3
    // normcdf would not be defined properly as the cpp file's definition of normcdf does not
    // contain static. vice versa if only in cpp but not the header file. and also if both is defined
    // static. Since it is NOT a static function
    // if not marking hornerFunction as static -> still works

    // 5.5.4
    // matlib.h seems suitable as all mathematical operations are conducted with matlib.h



    return 0;
}