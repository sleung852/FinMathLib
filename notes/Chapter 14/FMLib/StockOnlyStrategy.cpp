#include "StockOnlyStrategy.h"

double StockOnlyStrategy::chooseCharge(double stockPrice,  std::shared_ptr<ContinuousTimeOptionBase> option) {
	StockPriceModel pm = *getPricingModel();
    pm.setStockPrice(stockPrice);
    charge = option->price(pm);
	return charge;
}

double StockOnlyStrategy::selectStockQuantity(double date, double assetPrice) {
    return charge/assetPrice;
}