#include "matlib.h"

#include "Histogram.h"
#include "LineChart.h"
#include "RealFunction.h"
#include "geometry.h"
#include "testing.h"
#include <memory>
#include <random>

using namespace std;

/*  Create a linearly spaced vector */
Matrix linspace(double from, double to, int numPoints, bool rowVector) {
  ASSERT(numPoints >= 2);
  int nrows, ncols;
  if (rowVector) {
    nrows = 1;
    ncols = numPoints;
  } else {
    nrows = numPoints;
    ncols = 1;
  }
  Matrix ret(nrows, ncols);
  double step = (to - from) / (numPoints - 1);
  double current = from;
  for (int i = 0; i < numPoints; i++) {
    ret(i) = current;
    current += step;
  }
  return ret;
}

/**
 *  Sum the rows of a matrix
 */
Matrix sumRows(const Matrix &m) {
  int nrow = m.nRows();
  int ncol = m.nCols();
  Matrix ret(nrow, 1, 0);
  for (int row = 0; row < nrow; row++) {
    double total = 0.0;
    const double *start = m.begin() + m.offset(row, 0);
    for (int col = 0; col < ncol; col++) {
      total += *(start);
      start += nrow;
    }
    ret(row, 0) = total;
  }
  return ret;
}

/**
 *  Sum the cols of a matrix
 */
Matrix sumCols(const Matrix &m) {
  int ncol = m.nCols();
  Matrix ret(1, ncol, 0);
  for (int col = 0; col < ncol; col++) {
    double total = 0.0;
    const double *start = m.begin() + m.offset(0, col);
    const double *end = start + m.nRows();
    while (start != end) {
      total += *(start++);
    }
    ret(0, col) = total;
  }
  return ret;
}

/**
 *  The mean of the rows of a matrix
 */
Matrix meanRows(const Matrix &m) {
  Matrix ret = sumRows(m);
  ret *= (1.0 / m.nCols());
  return ret;
}

/**
 *  The mean of the cols of a matrix
 */
Matrix meanCols(const Matrix &m) {
  Matrix ret = sumCols(m);
  ret *= (1.0 / m.nRows());
  return ret;
}

/*  Compute the standard deviation of a matrix's rows */
Matrix stdRows(const Matrix &m, bool population) {
  int n = m.nCols();
  Matrix total(m.nRows(), 1);
  Matrix totalSq(m.nRows(), 1);
  for (int i = 0; i < n; i++) {
    Matrix val = m.col(i);
    total += val;
    val.times(val);
    totalSq += val;
  }
  Matrix val = total;
  val.times(val);
  val *= (-1.0) / n;
  val += totalSq;
  double factor = population ? (1.0) / n : (1.0) / (n - 1);
  val *= factor;
  val.sqrt();
  return val;
}

/*  Compute the standard deviation of a matrix's cols */
Matrix stdCols(const Matrix &m, bool population) {
  int n = m.nRows();
  Matrix total(1, m.nCols(), 1);
  Matrix totalSq(1, m.nCols(), 1);
  for (int i = 0; i < n; i++) {
    Matrix val = m.row(i);
    total += val;
    val.times(val);
    totalSq += val;
  }
  Matrix val = total;
  val.times(val);
  val *= (-1.0) / n;
  val += totalSq;
  double factor = population ? (1.0) / n : (1.0) / (n - 1);
  val *= factor;
  val.sqrt();
  return val;
}

/**
 *   Find the minimum across the cols of a vector
 */
Matrix minOverCols(const Matrix &m) {
  Matrix minRow = m.row(0);
  for (int i = 1; i < m.nRows(); i++) {
    Matrix currentRow = m.row(i);
    Matrix test = currentRow < minRow;
    test.test(currentRow, minRow);
    minRow = test;
  }
  return minRow;
}

/**
 *   Find the minimum across the cols of a vector
 */
Matrix maxOverCols(const Matrix &m) {
  Matrix maxRow = m.row(0);
  for (int i = 1; i < m.nRows(); i++) {
    Matrix currentRow = m.row(i);
    Matrix test = currentRow > maxRow;
    test.test(currentRow, maxRow);
    maxRow = test;
  }
  return maxRow;
}

/**
 *   Find the minimum across the rows of a vector
 */
Matrix minOverRows(const Matrix &m) {
  Matrix minCol = m.col(0);
  for (int i = 1; i < m.nCols(); i++) {
    Matrix currentCol = m.col(i);
    Matrix test = currentCol < minCol;
    test.test(currentCol, minCol);
    minCol = test;
  }
  return minCol;
}

/**
 *   Find the minimum across the rows of a vector
 */
Matrix maxOverRows(const Matrix &m) {
  Matrix maxCol = m.col(0);
  for (int i = 1; i < m.nCols(); i++) {
    Matrix currentCol = m.col(i);
    Matrix test = currentCol > maxCol;
    test.test(currentCol, maxCol);
    ;
    maxCol = test;
  }
  return maxCol;
}

/*  MersenneTwister random number generator */
static mt19937 mersenneTwister;
/*  Mutex to protect static var */
static mutex rngMutex;

/*  Reset the random number generator.
We ignore the description string */
void rng(const string &description) {
  ASSERT(description == "default");
  lock_guard<mutex> lock(rngMutex);
  mersenneTwister.seed(mt19937::default_seed);
}

/*  Generate random numbers */
Matrix randuniform(int rows, int cols) {
  lock_guard<mutex> lock(rngMutex);
  return randuniform(mersenneTwister, rows, cols);
}

/*  Create uniformly distributed random numbers using
the Mersenne Twister algorithm. See the code above for the answer
to the homework excercise which should familiarize you with the C API*/
Matrix randuniform(mt19937 &random, int rows, int cols) {
  Matrix ret(rows, cols, 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ret(i, j) = (random() + 0.5) / (random.max() + 1.0);
    }
  }
  return ret;
}

/**
 *  Generate random numbers
 */
Matrix randn(int rows, int cols) {
  lock_guard<mutex> lock(rngMutex);
  return randn(mersenneTwister, rows, cols);
}

/*  Create normally distributed random numbers */
Matrix randn(mt19937 &random, int rows, int cols) {
  Matrix ret = randuniform(random, rows, cols);
  for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
      ret(i, j) = norminv(ret(i, j));
    }
  }
  return ret;
}
/**
 *  Sort the rows of a matrix
 */
Matrix sortRows(const Matrix &m) {
  Matrix copy(m.nRows(), m.nCols(), 0);
  for (int i = 0; i < m.nRows(); i++) {
    vector<double> row = m.row(i).rowVector();
    std::sort(row.begin(), row.end());
    Matrix asMatrix(row, 1);
    copy.setRow(i, asMatrix, 0);
  }
  return copy;
}

/**
 *  Sort the rows of a matrix
 */
Matrix sortCols(const Matrix &m) {
  Matrix copy(m.nRows(), m.nCols(), 0);
  for (int i = 0; i < m.nCols(); i++) {
    vector<double> col = m.col(i).colVector();
    std::sort(col.begin(), col.end());
    Matrix asMatrix(col);
    copy.setCol(i, asMatrix, 0);
  }
  return copy;
}

/**
 *  Find the given percentile of a distribution
 */
static double prctile(const std::vector<double> &in, double percentage) {
  // See the MATLAB documentation for a specification of what prctile actually
  // does its a little fiddly. The tests were all computed using MATLAB
  ASSERT(percentage >= 0.0);
  ASSERT(percentage <= 100.0);
  int n = in.size();

  vector<double> sorted = in;
  std::sort(sorted.begin(), sorted.end());

  int indexBelow = (int)(n * percentage / 100.0 - 0.5);
  int indexAbove = indexBelow + 1;
  if (indexAbove > n - 1) {
    return sorted[n - 1];
  }
  if (indexBelow < 0) {
    return sorted[0];
  }
  double valueBelow = sorted[indexBelow];
  double valueAbove = sorted[indexAbove];
  double percentageBelow = 100.0 * (indexBelow + 0.5) / n;
  double percentageAbove = 100.0 * (indexAbove + 0.5) / n;
  if (percentage <= percentageBelow) {
    return valueBelow;
  }
  if (percentage >= percentageAbove) {
    return valueAbove;
  }
  double correction = (percentage - percentageBelow) *
                      (valueAbove - valueBelow) /
                      (percentageAbove - percentageBelow);
  return valueBelow + correction;
}

/**
 *   Return the given percentile on each row
 */
Matrix prctileRows(const Matrix &m, double percentage) {
  Matrix ret(m.nRows(), 1, 0);
  for (int i = 0; i < m.nRows(); i++) {
    vector<double> row = m.row(i).rowVector();
    ret(i) = prctile(row, percentage);
  }
  return ret;
}

/**
 *   Return the given percentile on each column
 */
Matrix prctileCols(const Matrix &m, double percentage) {
  Matrix ret(1, m.nCols(), 0);
  for (int i = 0; i < m.nCols(); i++) {
    vector<double> col = m.col(i).colVector();
    ret(i) = prctile(col, percentage);
  }
  return ret;
}

/**
 *  Convenience method for generating plots
 */
void plot(const string &file, const Matrix &x, const Matrix &y) {
  LineChart lc;
  lc.setSeries(x.asVector(), y.asVector());
  lc.writeAsHTML(file);
}

/**
 *  Convenience method for generating plots
 */
void hist(const string &file, const Matrix &data, int numBuckets) {
  Histogram h;
  h.setData(data.asVector());
  h.writeAsHTML(file);
}

const double ROOT_2_PI = sqrt(2.0 * PI);

static inline double hornerFunction(double x, double a0, double a1) {
  return a0 + x * a1;
}

static inline double hornerFunction(double x, double a0, double a1, double a2) {
  return a0 + x * hornerFunction(x, a1, a2);
}

static inline double hornerFunction(double x, double a0, double a1, double a2,
                                    double a3) {
  return a0 + x * hornerFunction(x, a1, a2, a3);
}

static inline double hornerFunction(double x, double a0, double a1, double a2,
                                    double a3, double a4) {
  return a0 + x * hornerFunction(x, a1, a2, a3, a4);
}

static inline double hornerFunction(double x, double a0, double a1, double a2,
                                    double a3, double a4, double a5) {
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5);
}

static inline double hornerFunction(double x, double a0, double a1, double a2,
                                    double a3, double a4, double a5,
                                    double a6) {
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6);
}

static inline double hornerFunction(double x, double a0, double a1, double a2,
                                    double a3, double a4, double a5, double a6,
                                    double a7) {
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6, a7);
}

static inline double hornerFunction(double x, double a0, double a1, double a2,
                                    double a3, double a4, double a5, double a6,
                                    double a7, double a8) {
  return a0 + x * hornerFunction(x, a1, a2, a3, a4, a5, a6, a7, a8);
}

/**
 *  Arguably this is a little easier to read than the original normcdf
 *  function as it makes the use of horner's method obvious.
 */
double normcdf(double x) {
  if (x <= 0) {
    return 1 - normcdf(-x);
  }
  double k = 1 / (1 + 0.2316419 * x);
  double poly = hornerFunction(k, 0.0, 0.319381530, -0.356563782, 1.781477937,
                               -1.821255978, 1.330274429);
  double approx = 1.0 - 1.0 / ROOT_2_PI * exp(-0.5 * x * x) * poly;
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

double norminv(double x) {
  // We use Moro's algorithm
  double y = x - 0.5;
  if (y < 0.42 && y > -0.42) {
    double r = y * y;
    return y * hornerFunction(r, a0, a1, a2, a3) /
           hornerFunction(r, 1.0, b1, b2, b3, b4);
  } else {
    double r;
    if (y < 0.0) {
      r = x;
    } else {
      r = 1.0 - x;
    }
    double s = log(-log(r));
    double t = hornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
    if (x > 0.5) {
      return t;
    } else {
      return -t;
    }
  }
}

/**
 *   Evaluate an integral using the rectangle rule
 */
double integral(function<double(double)> f, double a, double b, int nPoints) {
  double h = (b - a) / nPoints;
  double x = a + 0.5 * h;
  double total = 0.0;
  for (int i = 0; i < nPoints; i++) {
    double y = f(x);
    total += y;
    x += h;
  }
  return h * total;
}

/**
 *   Perform a substitution then integate the given
 *   real function from x to infinity by the rectangle rule
 */
double integralToInfinity(function<double(double)> f, double x, int nPoints) {
  auto i = [&](double s) { return 1 / (s * s) * f(1 / s + x - 1); };
  return integral(i, 0, 1, nPoints);
}

double integralFromInfinity(function<double(double)> f, double x, int nPoints) {
  auto i = [&](double t) { return f(-t); };
  return integralToInfinity(i, -x, nPoints);
}

double integralOverR(function<double(double)> f, int nPoints) {
  return integralToInfinity(f, 0, nPoints) +
         integralFromInfinity(f, 0, nPoints);
}

/**
 *   Creates a matrix of zeros
 */
Matrix zeros(int rows, int cols) { return Matrix(rows, cols); }

/**
 *   Creates a matrix of ones
 */
Matrix ones(int rows, int cols) {
  Matrix m = Matrix(rows, cols);
  for (double *p = m.begin(); p != m.end(); p++) {
    *p = 1;
  }
  return m;
}

Matrix transpose(const Matrix &in) {
  Matrix ret(in.nCols(), in.nRows(), false);
  for (int i = 0; i < in.nRows(); i++) {
    for (int j = 0; j < in.nCols(); j++) {
      ret(j, i) = in(i, j);
    }
  }
  return ret;
}

/*  Compute the cholesky decomposition */
Matrix chol(const Matrix &A) {
  int n = A.nRows();
  ASSERT(n == A.nCols());
  Matrix L(n, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      double s = A(i, j);
      for (int k = 0; k < j; k++) {
        s -= L(i, k) * L(j, k);
      }
      L(i, j) = s / L(j, j);
    }
    double s = A(i, i);
    for (int k = 0; k < i; k++) {
      s -= L(i, k) * L(i, k);
    }
    ASSERT(s >= 0); /* A must be positive definite */
    L(i, i) = sqrt(s);
  }
  return L;
}

double meanMultiThread(const std::vector<double> &vec, int threads) {
  double output = 0;
  int splitSize = vec.size() / threads;

  class ComputeSumTask : public Task {
  public:
    double sum;
    const std::vector<double> &vec;
    int start;
    int end;
    void execute() {
      for (int i = start; i < end; i++) {
        sum += vec.at(i);
      }
    }

    ComputeSumTask(const std::vector<double> &vec, int start, int end)
        : vec(vec), start(start), end(end) {
      sum = 0;
    };
  };

  std::vector<std::shared_ptr<ComputeSumTask>> tasks;

  for (int i = 0; i < threads - 1; i++) {
    tasks.push_back(std::make_shared<ComputeSumTask>(vec, i * splitSize,
                                                     (i + 1) * splitSize));
  }
  tasks.push_back(std::make_shared<ComputeSumTask>(
      vec, (threads - 1) * splitSize, vec.size()));

  std::shared_ptr<Executor> executor = Executor::newInstance();
  for (int i = 0; i < threads; i++) {
    executor->addTask(tasks[i]);
  }
  executor->join();

  for (int i = 0; i < threads; i++) {
    output += tasks[i]->sum;
  }
  return output / vec.size();
}

static bool isfinitenumber(double arg) {
  return arg == arg && arg != std::numeric_limits<double>::infinity() &&
         arg != -std::numeric_limits<double>::infinity();
}

double integrate2d(function<double(double, double)> f, int ai, int bi, int aj,
                   int bj, int n) {
  Matrix xi = randuniform(n, 1) * (bi - ai) + ai;
  Matrix xj = randuniform(n, 1) * (bj - aj) + aj;
  double output = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      double result = f(xi(i), xj(j));
      if (isfinitenumber(result)) {
        output += result * (bi - ai) * (bj - aj) / (n * n);
      }
    }
  }
  stringstream ss;
  ss << "Output=" << output << "\n";
  DEBUG_PRINT(ss.str());
  return output;
}

// double integrate2d(std::function<double(double, double)> f, int ai, int bi,
// int aj, int bj, int n) {
//     Matrix xi = randuniform(n,1) * (bi-ai) + ai;
//     Matrix xj = randuniform(n,1) * (bj-aj) + aj;
//     double output=0;

//     for (int i=0; i<n; i++) {
//         double result = f(xi(i), xj(i));
//         if (isfinitenumber(result)) {
//             output += result * (bi-ai) * (bj-aj) / n;
//         }
//     }
//     return output;
// }

double integrate2dMultithread(function<double(double, double)> f, int ai,
                              int bi, int aj, int bj, int n, int threads) {
  class Integral2DSingleThread : public Task {
  public:
    Integral2DSingleThread(function<double(double, double)> f, int threadIth,
                           int threadSize, mt19937 rng, int ai, int bi, int aj,
                           int bj, int n)
        : f(f), threadIth(threadIth), threadSize(threadSize), rng(rng), ai(ai),
          bi(bi), aj(aj), bj(bj), n(n) {
      localSum = 0;
    }
    void execute() {
      rng.discard(threadSize * threadIth);
      Matrix xi = randuniform(rng, threadSize, 1) * (bi - ai) + ai;
      Matrix xj = randuniform(rng, threadSize, 1) * (bj - aj) + aj;

      for (int i = 0; i < threadSize; i++) {
        double result = f(xi(i), xj(i));
        if (isfinitenumber(result)) {
          localSum += result * (bi - ai) * (bj - aj) / n;
        }
      }
    }

    function<double(double, double)> f;
    int threadIth;
    int threadSize;
    mt19937 rng;
    int ai;
    int bi;
    int aj;
    int bj;
    int n;
    double localSum;
  };
  shared_ptr<Executor> executor = Executor::newInstance();
  vector<shared_ptr<Integral2DSingleThread>> integralTasks;
  int threadSize = n / threads;
  for (int i = 0; i < threads; i++) {
    mt19937 rng;
    shared_ptr<Integral2DSingleThread> integralThread =
        make_shared<Integral2DSingleThread>(f, i, threadSize, rng, ai, bi, aj,
                                            bj, n);
    integralTasks.push_back(integralThread);
    executor->addTask(integralTasks[i]);
  }
  executor->join();
  double result = 0;
  for (int i = 0; i < threads; i++) {
    result += integralTasks[i]->localSum;
  }
  return result;
}

///////////////////////////////////////////////
//
//   TESTS
//
///////////////////////////////////////////////

static Matrix createTestVector() {
  Matrix v("1;5;3;9;7");
  return v;
}

static void testLinspace() {
  Matrix result = linspace(1.0, 10.0, 4);
  ASSERT_APPROX_EQUAL(result(0), 1.0, 0.001);
  ASSERT_APPROX_EQUAL(result(1), 4.0, 0.001);
  ASSERT_APPROX_EQUAL(result(2), 7.0, 0.001);
  ASSERT_APPROX_EQUAL(result(3, 0), 10.0, 0.001);
}

static void testSumRows() {

  Matrix m("1,2,3;4,5,6");
  Matrix expected = Matrix("6;15");
  expected.assertEquals(sumRows(m), 0.001);
  INFO(sumRows(m));

  m = Matrix(10, 10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      m(i, j) = j;
    }
  }
  Matrix s = sumRows(m);
  Matrix mean = meanRows(m);
  for (int j = 0; j < 10; j++) {
    double actual = s(j, 0);
    ASSERT_APPROX_EQUAL(actual, 45, 0.001);
    actual = mean(j, 0);
    ASSERT_APPROX_EQUAL(actual, 4.5, 0.001);
  }
}

static void testSumCols() {

  Matrix m = Matrix(10, 10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      m(i, j) = i;
    }
  }
  Matrix s = sumCols(m);
  Matrix mean = meanCols(m);
  for (int i = 0; i < 10; i++) {
    double actual = s(0, i);
    ASSERT_APPROX_EQUAL(actual, 45, 0.001);
    actual = mean(0, i);
    ASSERT_APPROX_EQUAL(actual, 4.5, 0.001);
  }
}

static void testStandardDeviation() {
  ASSERT_APPROX_EQUAL(stdCols(createTestVector()).asScalar(), 3.1623, 0.001);
  ASSERT_APPROX_EQUAL(stdCols(createTestVector(), true).asScalar(), 2.8284,
                      0.001);
}

static void testRanduniform() {
  rng("default");
  Matrix m = randuniform(1000, 1);
  ASSERT(m.nRows() == 1000);
  ASSERT_APPROX_EQUAL(meanCols(m).asScalar(), 0.5, 0.1);
  ASSERT(maxOverCols(m).asScalar() < 1.0);
  ASSERT(minOverCols(m).asScalar() > 0.0);
}

static void testRandn() {
  rng("default");
  Matrix m = randn(10000, 1);
  ASSERT(m.nRows() == 10000);
  ASSERT_APPROX_EQUAL(meanCols(m).asScalar(), 0.0, 0.1);
  ASSERT_APPROX_EQUAL(stdCols(m).asScalar(), 1.0, 0.1);
}

static void testNormCdf() { ASSERT_APPROX_EQUAL(normcdf(1.96), 0.975, 0.001); }

static void testNormInv() { ASSERT_APPROX_EQUAL(norminv(0.975), 1.96, 0.01); }

static void testPrctile() {
  const vector<double> v = createTestVector().colVector();
  ASSERT_APPROX_EQUAL(prctile(v, 100.0), 9.0, 0.001);
  ASSERT_APPROX_EQUAL(prctile(v, 0.0), 1.0, 0.001);
  ASSERT_APPROX_EQUAL(prctile(v, 50.0), 5.0, 0.001);
  ASSERT_APPROX_EQUAL(prctile(v, 17.0), 1.7, 0.001);
  ASSERT_APPROX_EQUAL(prctile(v, 62.0), 6.2, 0.001);

  Matrix m("1,2,3;4,5,6");
  Matrix("2;5").assertEquals(prctileRows(m, 50.0), 0.001);
  m = Matrix("1,2,3;4,5,6");
  Matrix("2.5,3.5,4.5").assertEquals(prctileCols(m, 50.0), 0.001);
}

/*  To test the integral function, we need a function
    to integrate */
class SinFunction : public RealFunction {
  double evaluate(double x);
};

double SinFunction::evaluate(double x) { return sin(x); }

static void testIntegral() {
  SinFunction integrand;
  double actual = integral(integrand, 1, 3, 1000);
  double expected = -cos(3.0) + cos(1.0);
  ASSERT_APPROX_EQUAL(actual, expected, 0.000001);
}

/**
 *  When you create a small class like this, using
 *  nested classes is easier.
 */
static void testIntegralVersion2() {

  class Sin : public RealFunction {
    double evaluate(double x) { return sin(x); }
  };

  Sin integrand;
  double actual = integral(integrand, 1, 3, 1000);
  double expected = -cos(3.0) + cos(1.0);
  ASSERT_APPROX_EQUAL(actual, expected, 0.000001);
}

static void testIntegral3() {
  auto integrand = [](double x) { return sqrt(1 + pow(sin(x), 2.0)); };
  double res = integral(integrand, 0, PI, 1000);
  ASSERT_APPROX_EQUAL(res, 3.820197789, 0.001);
}

static void testInfiniteIntegrals() {
  auto normPDF = [](double x) { return 1 / ROOT_2_PI * exp(-0.5 * x * x); };
  ASSERT_APPROX_EQUAL(integralOverR(normPDF, 1000), 1.0, 0.01);
}

static void testMinOverRows() {
  Matrix m("1,2,3;4,5,6");
  Matrix expected("1;4");
  expected.assertEquals(minOverRows(m), 0.001);
}

static void testMaxOverRows() {
  Matrix m("1,2,3;4,5,6");
  Matrix expected("3;6");
  INFO("Expected " << expected);
  INFO("Actual " << maxOverRows(m));
  expected.assertEquals(maxOverRows(m), 0.001);
}

static void testMinOverCols() {
  Matrix m("1,2,3;4,5,6");
  Matrix expected("1,2,3");
  expected.assertEquals(minOverCols(m), 0.001);
}

static void testMaxOverCols() {
  Matrix m("1,2,3;4,5,6");
  Matrix expected("4,5,6");
  expected.assertEquals(maxOverCols(m), 0.001);
}

static void testSortRows() {
  Matrix m("3,2,1");
  Matrix expected("1,2,3");
  expected.assertEquals(sortRows(m), 0.001);
}

static void testSortCols() {
  Matrix m("3;2;1");
  Matrix expected("1;2;3");
  expected.assertEquals(sortCols(m), 0.001);
}

static void testTranspose() {
  Matrix m("3;2;1");
  Matrix expected("3,2,1");
  expected.assertEquals(transpose(m), 0.001);
}

static void testChol() {
  Matrix m("3,1,2;1,4,-1;2,-1,5");
  Matrix c = chol(m);
  Matrix product = c * transpose(c);
  m.assertEquals(product, 0.001);
}

static void testMultiThreadMeanVec() {
  vector<double> egVec(100);
  for (int i = 0; i < 100; i++) {
    egVec[i] = i * i + 3 * i + 4;
  }
  double actual = meanMultiThread(egVec, 4);

  auto mean = [](vector<double> vec) {
    double out = 0;
    for (int i = 0; i < vec.size(); i++) {
      out += vec[i];
    }
    return out / vec.size();
  };
  double expect = mean(egVec);
  // cout << "Actual: " << actual << endl;
  // cout << "Expect: " << expect << endl;
  ASSERT_APPROX_EQUAL(actual, expect, 0.01);
}

// static void testIntegrate2d() {
//     auto sphere = [](double x, double y) {
//         return sqrt(1 - x*x - y*y);
//     };
//     double actual = integrate2d(sphere, 0, 1, 0, 1, 10000);
//     double expect = PI * 4 / 3 / 2;
//     cout << "Actual: " << actual << endl;
//     cout << "Expect: " << expect << endl;
//     ASSERT_APPROX_EQUAL(actual, expect, 1);
// }

static void testIntegrate2d() {
  // Rectangle rect(6.0, 2.0, 1.0, 3.0);
  auto f = [](double x, double y) { return sin(x) + cos(y); };
  double integral = integrate2d(f, 1.0, 3.0, 2.0, 6.0, 10000);
  double expected = 2 * ((-1 + 4 * sin(1)) * sin(2) + sin(6));
  // cout << "Actual: " << integral << endl;
  // cout << "Expect: " << expected << endl;
  ASSERT_APPROX_EQUAL(integral, expected, 0.2);
}

static void testIntegrate2dv2() {
  // Rectangle rect(6.0, 2.0, 1.0, 3.0);
  auto f = [](double x, double y) { return sin(x) + cos(y); };
  double integral = integrate2d(f, 1.0, 3.0, 2.0, 6.0, 10000);
  double integralMultiThread =
      integrate2dMultithread(f, 1.0, 3.0, 2.0, 6.0, 10000, 4);
  // cout << "integral: " << integral << endl;
  // cout << "integralMultiThread: " << integralMultiThread << endl;
  ASSERT_APPROX_EQUAL(integral, integralMultiThread, 0.1);
}

void testMatlib() {
  TEST(testLinspace);
  TEST(testSumRows);
  TEST(testSumCols);
  TEST(testStandardDeviation);
  TEST(testRanduniform);
  TEST(testRandn);
  TEST(testNormInv);
  TEST(testNormCdf);
  TEST(testPrctile);
  TEST(testIntegral);
  TEST(testIntegralVersion2);
  TEST(testInfiniteIntegrals);
  TEST(testMaxOverRows);
  TEST(testMinOverRows);
  TEST(testMaxOverCols);
  TEST(testMinOverCols);
  TEST(testSortRows);
  TEST(testSortCols);
  TEST(testTranspose);
  TEST(testChol);
  TEST(testIntegral3);
  TEST(testMultiThreadMeanVec);
  setDebugEnabled(true);
  TEST(testIntegrate2d);
  TEST(testIntegrate2dv2);
  setDebugEnabled(false);
}
