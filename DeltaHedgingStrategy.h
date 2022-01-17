#ifndef E887B337_58F9_4364_B591_C8C453087D7F
#define E887B337_58F9_4364_B591_C8C453087D7F

#include "stdafx.h"
#include "Strategy.h"

class DeltaHedgingStrategy : public Strategy {
    public:
        Matrix selectStockQuantity(double date, Matrix assetPrices);
        double selectStockQuantity(double date, double assetPrice);
        // double chooseCharge(double assetPrice,  std::shared_ptr<ContinuousTimeOptionBase> option);

        void setToHedge(std::shared_ptr<ContinuousTimeOptionBase> option) {
            toHedge = option;
        }

    private:
        std::shared_ptr<ContinuousTimeOptionBase> toHedge;

};

void testDeltaHedgingStrategy();

#endif /* E887B337_58F9_4364_B591_C8C453087D7F */
