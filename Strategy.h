#ifndef A800BA55_3190_4D63_84D0_527C5870F81F
#define A800BA55_3190_4D63_84D0_527C5870F81F

// #include "StockPriceModel.h"
#include "BlackScholesModel.h"
#include "ContinuousTimeOptionBase.h"
#include <memory>

class Strategy {
    public:
        virtual ~Strategy(){};

        std::shared_ptr<BlackScholesModel> getPricingModel() {
            return this->pricingModel;
        }
        void setPricingModel(std::shared_ptr<BlackScholesModel> model) {
            // create a copy
            this->pricingModel = model;
            // pricingModel = std::make_shared<StockPriceModel>(*model);
        }

        virtual double chooseCharge(double assetPrice,  std::shared_ptr<ContinuousTimeOptionBase> option);

        virtual Matrix selectStockQuantity(double date, Matrix assetPrices)=0;

        virtual double selectStockQuantity(double date, double assetPrice)=0;


    private:
        std::shared_ptr<BlackScholesModel> pricingModel;
        /*  How much should we charge the customer */
        // double chooseCharge(double assetPrice,  std::shared_ptr<ContinuousTimeOptionBase> option);
        /*  How much stock/bond should we hold */
        

};

#endif /* A800BA55_3190_4D63_84D0_527C5870F81F */
