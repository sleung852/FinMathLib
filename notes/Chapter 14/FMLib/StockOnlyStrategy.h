#ifndef F82596B3_2922_4BA7_B651_1BD34FE69BE7
#define F82596B3_2922_4BA7_B651_1BD34FE69BE7

#include "stdafx.h"
#include "Strategy.h"

class StockOnlyStrategy : public Strategy {
    public:
        double selectStockQuantity(double date, double assetPrice);
        double chooseCharge(double assetPrice,  std::shared_ptr<ContinuousTimeOptionBase> option);

    private:
        double charge;
};

#endif /* F82596B3_2922_4BA7_B651_1BD34FE69BE7 */
