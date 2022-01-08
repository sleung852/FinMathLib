#include "geometry.h"
#include "testing.h"

double calculateCircleCircumference(double radius) {
    DEBUG_PRINT("Circle Cirumference Radius: " << radius << "\n");
    return radius*2*PI;
}

double calculateCircleArea(double radius) {
    DEBUG_PRINT("Circle Area Radius: " << radius << "\n");
    return radius * radius * PI;
}

// TEST

static void test_calculateCircleCircumference() {
    // test bounds
    ASSERT (calculateCircleCircumference(0.3) < (0.3+0.3)*4); // less than a square circumference
    ASSERT (calculateCircleCircumference(0.3) > (0.3*4)); // less than a square circumference
    // simple example
    ASSERT_APPROX_EQUAL(calculateCircleCircumference(1), 3.14*2*1, 0.01);
    // test increasing
    ASSERT (calculateCircleCircumference(0.3) > calculateCircleCircumference(0.2)); 
}

static void test_calculateCircleArea() {
    // test bounds
    ASSERT (calculateCircleArea(0.3) < ((0.3+0.3)*(0.3+0.3))); // less than a square area
    ASSERT (calculateCircleArea(0.3) > (0.3 * 0.3)); // less than a square area
    // simple example
    ASSERT_APPROX_EQUAL(calculateCircleArea(1), 3.14*1, 0.01);
    // test increasing 
    ASSERT (calculateCircleArea(0.3) > calculateCircleArea(0.2)); 
}

void testGeometric(){
    setDebugEnabled(true);
    TEST( test_calculateCircleCircumference );
    TEST( test_calculateCircleArea );
    setDebugEnabled(false);
}