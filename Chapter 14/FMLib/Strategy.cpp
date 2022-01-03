#include "Strategy.h"

double Strategy::chooseCharge(double stockPrice,  std::shared_ptr<ContinuousTimeOptionBase> option) {
	StockPriceModel pm = *getPricingModel();
    pm.setStockPrice(stockPrice);
	return option->price(pm);
}