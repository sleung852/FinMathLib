#ifndef AAED6EB3_40E5_4367_9C6A_9905FC5C9E7D
#define AAED6EB3_40E5_4367_9C6A_9905FC5C9E7D

#include "PathIndependentOption.h"

/*
Write DigitalCallOption and DigitalPutOption classes.
Refactor PutOption so it extends PathIndependentOption.
*/

class DigitalCallOption : public PathIndependentOption {
    public:
        double payoff(double endStockPrice) const;
};

#endif /* AAED6EB3_40E5_4367_9C6A_9905FC5C9E7D */
