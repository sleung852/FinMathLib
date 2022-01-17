#include "BondsOnlyStrategy.h"

double BondsOnlyStrategy::selectStockQuantity(double date, double assetPrice) {
    return 0.0;
}

Matrix BondsOnlyStrategy::selectStockQuantity(double date, Matrix assetPrice) {
    return Matrix(assetPrice.nRows(), 1, 1);
}