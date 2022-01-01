#ifndef A646B88C_7F94_4E36_97D8_7972104D9099
#define A646B88C_7F94_4E36_97D8_7972104D9099

#include "PathIndependentOption.h"

class DigitalPutOption : public PathIndependentOption {
    public:
        double payoff(double endStockPrice) const;
};

#endif /* A646B88C_7F94_4E36_97D8_7972104D9099 */
