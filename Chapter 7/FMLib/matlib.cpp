#include "matlib.h"
#include "geometry.h"

using namespace std;

const double ROOT_2_PI = sqrt( 2.0 * PI );


static inline double hornerFunction( double x, double a0, double a1) {
	return a0 + x*a1;
}

static inline double hornerFunction( double x, double a0, double a1, double a2) {
	return a0 + x*hornerFunction( x, a1, a2);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3) {
	return a0 + x*hornerFunction( x, a1, a2, a3);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5, double a6) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5, double a6, double a7) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double hornerFunction( double x, double a0, double a1, double a2, double a3, double a4,
					   double a5, double a6, double a7, double a8) {
	return a0 + x*hornerFunction( x, a1, a2, a3, a4, a5, a6, a7, a8);
}

/**
 *  Arguably this is a little easier to read than the original normcdf
 *  function as it makes the use of horner's method obvious.
 */
double normcdf( double x ) {
    DEBUG_PRINT( "normcdf("<<x<<")");
	if (x<0) {
		return 1-normcdf(-x);
	}
	double k = 1/(1 + 0.2316419*x);
	double poly = hornerFunction(k,
								 0.0, 0.319381530, -0.356563782,
								 1.781477937,-1.821255978,1.330274429);
	double approx = 1.0 - 1.0/ROOT_2_PI * exp(-0.5*x*x) * poly;
	return approx;
}

/*  Constants required for Moro's algorithm */
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;

double norminv( double x ) {
	// We use Moro's algorithm
    DEBUG_PRINT( "norminv(" << x <<")" );
	double y = x - 0.5;
	if (y<0.42 && y>-0.42) {
		double r = y*y;
        DEBUG_PRINT( "Case 1, r=" << r );
		return y*hornerFunction(r,a0,a1,a2,a3)/hornerFunction(r,1.0,b1,b2,b3,b4);
	} else {
		double r;
		if (y<0.0) {
			r = x;
		} else {
			r = 1.0 - x;
		}
        DEBUG_PRINT( "Case 2, r=" << r);
		double s = log( -log( r ));
		double t = hornerFunction(s,c0,c1,c2,c3,c4,c5,c6,c7,c8);
		if (x>0.5) {
			return t;
		} else {
			return -t;
		}
	}
}

// 7.7.2
double mean(const vector<double> &v){
	double sum = 0;
	for (size_t i=0; i<v.size(); i++) {
		sum += v.at(i);
	}
	return sum/static_cast<double>(v.size());
}

// 7.7.3
double standardDeviation(const vector<double> &v, bool sample) {
	double mu = mean(v);
	double sum_diff_sq = 0;
	for (size_t i=0; i<v.size(); i++) {
		sum_diff_sq += pow(v.at(i) - mu, 2);
	}
	if (sample) return sqrt(sum_diff_sq/(v.size()-1));
	else return sqrt(sum_diff_sq/v.size());
}

// 7.7.4
double max(vector<double> v) {
	if (v.size() == 0) throw logic_error("The input vector is empty!");
	double max_val = v.at(0);
	if (v.size() == 1) return max_val;
	for (size_t i=1; i<v.size(); i++) {
		if (v.at(i) > max_val) max_val = v.at(i);
	}
	return max_val;
}

double min(vector<double> v) {
	if (v.size() == 0) throw logic_error("The input vector is empty!");
	double min_val = v.at(0);
	if (v.size() == 1) return min_val;
	for (size_t i=1; i<v.size(); i++) {
		if (v.at(i) < min_val) min_val = v.at(i);
	}
	return min_val;
}

// 7.7.5
double randuni() {
	return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

vector<double> randuniform(int n) {
	vector<double> out_v(n, 0.0);
	for (int i=0; i<n; i++) {
		out_v.at(i) = randuni();
	}
	return out_v;
}

// 7.7.6
double normalDist(double x, double mu, double sigma) {
	return 1/(sigma * sqrt(2*PI)) * exp(-0.5*pow((x-mu)/sigma,2));
}

// 7.7.7
double boxMullerCos() {
	return sqrt(-2 * log(randuni())) * cos(2*PI*randuni());
}

double boxMullerSin() {
	return sqrt(-2 * log(randuni())) * sin(2*PI*randuni());
}

vector<double> randn(int n) {
	vector<double> out_v(n, 0.0);
	default_random_engine generator;
  	normal_distribution<double> distribution(0.0,1.0);
	for (int i=0; i<n; i++) {
		out_v.at(i) = distribution(generator);
	}
	return out_v;
}

vector<double> randnAlt(int n) {
	vector<double> out_v(n, 0.0);
	for (int i=0; i<n; i++) {
		if (randuni() > 0.5) out_v.at(i) = boxMullerCos();
		else out_v.at(i) = boxMullerSin();
	}
	return out_v;
}

// 7.7.9
double prctile(std::vector<double> v, double p) {
	vector<double> v_copy(v);
	sort(v_copy.begin(), v_copy.end());
	int i = round(static_cast<double>(v.size()-1) * p / 100.0);
	return v_copy.at(i);
}

///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////

void testNormCdf() {
    ASSERT_APPROX_EQUAL( normcdf( 1.96 ), 0.975, 0.001 );
}

void testNormInv() {
    ASSERT_APPROX_EQUAL( norminv( 0.975 ), 1.96, 0.01 );
}

static vector<double> createTestVector() {
	return vector<double>({1,2,3,4,5});
}

// 7.7.2
void testMean() {
	vector<double> vector_eg = createTestVector();
    ASSERT_APPROX_EQUAL( mean(vector_eg), 3, 0.01 );
	vector_eg.pop_back();
    ASSERT_APPROX_EQUAL( mean(vector_eg), 2.5, 0.01 );
}

// 7.7.3
void testStandardDeviation() {
	vector<double> vector_eg = createTestVector();
	// sum_diff_sq = 10
	// test sample sd -> 10/4 = 2.5
    ASSERT_APPROX_EQUAL( standardDeviation(vector_eg), sqrt(2.5), 0.01 );
	// test population sd -> 10/5 = 2.0
	ASSERT_APPROX_EQUAL( standardDeviation(vector_eg, false), sqrt(2.0), 0.01 );
}

// 7.7.4
void testMin() {
	vector<double> vector_eg = createTestVector();
	ASSERT_APPROX_EQUAL( min(vector_eg), 1.0, 0.01 );
}

void testMax() {
	vector<double> vector_eg = createTestVector();
	ASSERT_APPROX_EQUAL( max(vector_eg), 5.0, 0.01 );
}

// 7.7.5
void testRandUniform() {
	vector<double> v = randuniform(10);
	ASSERT((v.at(0)>=0.0) && (v.at(0)<=1.0));
	// for (size_t i=0; i<v.size(); i++) {
	// 	cout << v.at(i) << " ";
	// 	// DEBUG_PRINT("rand_uni: " << v.at(i));
	// 	ASSERT((v.at(i)>=0.0) && (v.at(i)<=1.0));
	// }
}

// 7.7.6
void testStandardNorm(const vector<double> &v) {
	double mu = mean(v);
	double st_d = standardDeviation(v);
	ASSERT_APPROX_EQUAL( mu, 0.0, 0.2 );
	ASSERT_APPROX_EQUAL( st_d, 1.0, 0.2 );
}

void testRandn() {
	vector<double> v = randn(100);
	testStandardNorm(v);
}

void testRandnAlt() {
	vector<double> v = randnAlt(100);
	testStandardNorm(v);
}

void testPrctile() {
	vector<double> v({ 4.0, 5.0, 3.0, 1.0 ,2.0});
	DEBUG_PRINT(prctile(v, 0));
	ASSERT(prctile(v, 0)==1.0);
	DEBUG_PRINT(prctile(v, 25));
	ASSERT(prctile(v, 25)==2.0);
	DEBUG_PRINT(prctile(v, 50));
	ASSERT(prctile(v, 50)==3.0);
	DEBUG_PRINT(prctile(v, 75));
	ASSERT(prctile(v, 75)==4.0);
	DEBUG_PRINT(prctile(v, 100));
	ASSERT(prctile(v, 100)==5.0);
}

void testMatlib() {
    setDebugEnabled(true);
    TEST( testNormInv );
    setDebugEnabled(false);
    TEST( testNormCdf );
	TEST( testMean );
	TEST( testStandardDeviation );
	TEST( testMin );
	TEST( testMax );
	setDebugEnabled(true);
	TEST ( testRandUniform );
	setDebugEnabled(false);
	TEST ( testRandn );
	TEST ( testRandnAlt );
	setDebugEnabled(true);
	TEST ( testPrctile );
	setDebugEnabled(false);
	
}
