#ifndef AD235130_F485_46A8_8904_2FFFF0A0826D
#define AD235130_F485_46A8_8904_2FFFF0A0826D

#include "stdafx.h"
#include "testing.h"
#include <iostream>

template <typename T>
class ComplexNumber {
    public:
        T x;
        T y;

        ComplexNumber();
        ComplexNumber(T real);

};

template <typename T>
ComplexNumber<T>::ComplexNumber() {
    x = 0;
    y = 0;
}

template <typename T>
ComplexNumber<T>::ComplexNumber(T real) {
    x = real;
    y = 0;
}

template <typename T>
ComplexNumber<T> operator+(const ComplexNumber<T>& lhs, const ComplexNumber<T>& rhs) {
    ComplexNumber<T> cNum;
    cNum.x = lhs.x + rhs.x;
    cNum.y = lhs.y + rhs.y;
    return cNum;
}

template <typename T>
bool operator==(const ComplexNumber<T>& lhs, const ComplexNumber<T>& rhs){
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

void testComplexNumber () {
    // test int
    ComplexNumber<int> cNumInt1;
    cNumInt1.x = 1;
    cNumInt1.y = 2;
    ComplexNumber<int> cNumInt2;
    cNumInt2.x = 3;
    cNumInt2.y = 4;
    ComplexNumber<int> cNumIntExp;
    cNumIntExp.x = 4;
    cNumIntExp.y = 6;
    ComplexNumber<int> cNumInt3 = (cNumInt1 + cNumInt2);
    // std::cout << cNumInt3.x << " " << cNumInt3.y << std::endl;
    // std::cout << cNumIntExp.x << " " << cNumIntExp.y << std::endl;
    ASSERT( cNumInt3 == cNumIntExp);

    // test floats
    ComplexNumber<float> cNumFloat1;
    cNumFloat1.x = 1.3;
    cNumFloat1.y = 2.4;
    ComplexNumber<float> cNumFloat2;
    cNumFloat2.x = 3.5;
    cNumFloat2.y = 4.6;
    ComplexNumber<float> cNumFloatExp;
    cNumFloatExp.x = 4.8;
    cNumFloatExp.y = 7.0;
    ASSERT(cNumFloat1 + cNumFloat2 == cNumFloatExp);

    // test double
    ComplexNumber<double> cNumDouble1;
    cNumDouble1.x = 1.3;
    cNumDouble1.y = 2.4;
    ComplexNumber<double> cNumDouble2;
    cNumDouble2.x = 3.5;
    cNumDouble2.y = 4.6;
    ComplexNumber<double> cNumDoubleExp;
    cNumDoubleExp.x = 4.8;
    cNumDoubleExp.y = 7.0;
    ASSERT(cNumDouble1 + cNumDouble2 == cNumDoubleExp);
}

#endif /* AD235130_F485_46A8_8904_2FFFF0A0826D */
