#ifndef D96A285C_AE3F_4D4C_8924_6D05AD530390
#define D96A285C_AE3F_4D4C_8924_6D05AD530390

#include "stdafx.h"
#include "BarrierOption.h"

class UpAndInOption : public BarrierOption {
    public:
        double payoff(const std::vector<double>& stockPrices) const;
};

#endif /* D96A285C_AE3F_4D4C_8924_6D05AD530390 */
