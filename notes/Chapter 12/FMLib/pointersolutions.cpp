#include "stdafx.h"
#include "testing.h"
#include "geometry.h"
#include <string>

using namespace std;



static void reverseDoubles(double* doubles, int length) {
	for (int i = 0; i < length / 2; i++) {
		double temp = doubles[i];
		int oppositeIndex = length - 1 - i;
		doubles[i] = doubles[oppositeIndex];
		doubles[oppositeIndex] = temp;
	}
}

static void testReverseDoubles() {
	double d[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	reverseDoubles(d, sizeof(d) / sizeof(double));
	ASSERT_APPROX_EQUAL(d[0], 5.0, 0.0001);
	ASSERT_APPROX_EQUAL(d[1], 4.0, 0.0001);
	ASSERT_APPROX_EQUAL(d[2], 3.0, 0.0001);
	ASSERT_APPROX_EQUAL(d[3], 2.0, 0.0001);
	ASSERT_APPROX_EQUAL(d[4], 1.0, 0.0001);
}

static void polarToCartesian(double r, double theta, double& x, double& y) {
	x = r*cos(theta);
	y = r*sin(theta);
}

static void testPolarToCartesian() {
	double x;
	double y;
	polarToCartesian(1, PI / 2, x, y);
	ASSERT_APPROX_EQUAL(x, 0.0, 0.0001);
	ASSERT_APPROX_EQUAL(y, 1.0, 0.0001);
}

/**
*  Is the string pointed to by shorter the first part of the string longer?
*/
static bool matches(const char* shorter, const char* longer) {
	while (true) {
		if (*shorter == 0) {
			return true;
		}
		if (*longer == 0) {
			return false;
		}
		if (*shorter != *longer) {
			return false;
		}
		shorter++;
		longer++;
	}
}

static int search(const char* needle, const char* haystack) {
	// this search algorithm is pretty crude, faster algorithms do exist
	int ret = 0;
	const char* ptr = haystack;
	while (*ptr != 0) {
		if (matches(needle, ptr)) {
			ret++;
		}
		ptr++;
	}
	return ret;
}

static void testSearch() {
	ASSERT(search("be", "to be or not to be") == 2);
}

void testPointerSolutions() {
	TEST(testReverseDoubles);
	TEST(testPolarToCartesian);
	TEST(testSearch);
}