#include "DownAndInOption.h"
#include "matlib.h"

using namespace std;

Matrix DownAndInOption::payoff(
        const Matrix& prices ) const {
    Matrix min = minOverRows( prices );
    Matrix didHit = min < getBarrier();
    Matrix p = prices.col( prices.nCols()-1);
    p -= getStrike();
    p.positivePart();
    p.times(didHit);
    return p;
}