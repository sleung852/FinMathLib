#ifndef D9564A88_972A_44D8_AF79_A40D3B371360
#define D9564A88_972A_44D8_AF79_A40D3B371360

#include "stdafx.h"
#include "BarrierOption.h"

class DownAndInOption : public BarrierOption {
    public:
        double payoff(const std::vector<double>& stockPrices) const;
};

#endif /* D9564A88_972A_44D8_AF79_A40D3B371360 */
