#include "StockOnlyStrategy.h"

double StockOnlyStrategy::chooseCharge(double stockPrice,  std::shared_ptr<ContinuousTimeOptionBase> option) {
	BlackScholesModel pm = *getPricingModel();
    pm.stockPrice = stockPrice;
    MultiStockModel msm(pm);
    charge =  option->price(msm);
    return charge;
}

double StockOnlyStrategy::selectStockQuantity(double date, double assetPrice) {
    return charge/assetPrice;
}

Matrix StockOnlyStrategy::selectStockQuantity(double date, Matrix assetPrice) {
    Matrix stockQt(assetPrice.nRows(), 1);
    for (int i=0; i<assetPrice.nRows(); i++) stockQt(i) = charge / assetPrice(i);
    return stockQt;
}