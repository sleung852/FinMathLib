#include "Strategy.h"
#include "MultiStockModel.h"

double Strategy::chooseCharge(double stockPrice,  std::shared_ptr<ContinuousTimeOptionBase> option) {
	BlackScholesModel pm = *getPricingModel();
    pm.stockPrice = stockPrice;
	MultiStockModel msm(pm);
	return option->price(msm);
}