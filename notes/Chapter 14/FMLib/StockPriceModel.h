#ifndef FAB489C8_F339_4255_9281_2DE5B81E19C3
#define FAB489C8_F339_4255_9281_2DE5B81E19C3

#include "stdafx.h"

class StockPriceModel {
    public:
        virtual ~StockPriceModel(){};

        std::vector<double> generatePricePath(
            double toDate,
            int nSteps) const;

        std::vector<double> generateRiskNeutralPricePath(
            double toDate,
            int nSteps) const;

        void setStockPrice(double stockPrice) {
            this->stockPrice = stockPrice;
        }
        double getStockPrice() const {
            return this->stockPrice;
        }

        void setRiskFreeRate(double riskFreeRate) {
            this->riskFreeRate = riskFreeRate;
        }
        double getRiskFreeRate() const {
            return this->riskFreeRate;
        }

        void setDate(double date) {
            this->date = date;
        }
        double getDate() const {
            return this->date;
        }

        void setDrift(double drift) {
            this->drift = drift;
        }
        double getDrift() const {
            return this->drift;
        }

        void setVolatility(double volatility) {
            this->volatility = volatility;
        }
        double getVolatility() const {
            return this->volatility;
        }

    private:

        virtual std::vector<double> generatePricePath(
                                double toDate,
                                int nSteps,
                                double drift) const;

        double stockPrice;
        double riskFreeRate;
        double date;
        double drift;
        double volatility;
};

#endif /* FAB489C8_F339_4255_9281_2DE5B81E19C3 */
