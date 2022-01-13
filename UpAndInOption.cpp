#include "UpAndInOption.h"
#include "matlib.h"

using namespace std;


Matrix UpAndInOption::payoff(
        const Matrix& prices ) const {
    Matrix max = maxOverRows( prices );
    Matrix didHit = max < getBarrier();
    Matrix p = prices.col( prices.nCols()-1);
    p -= getStrike();
    p.positivePart();
    p.times(didHit);
    return p;
}