#pragma once

#include "stdafx.h"
#include "StockPriceModel.h"

class BlackScholesModel : public StockPriceModel {
    public:
        BlackScholesModel();

        std::vector<double> generatePricePath(
                                double toDate,
                                int nSteps) const;

        std::vector<double> generateRiskNeutralPricePath(
                                double toDate,
                                int nSteps) const;

    private:
        std::vector<double> generatePricePath(
                                double toDate,
                                int nSteps,
                                double drift) const;
};



void testBlackScholesModel();