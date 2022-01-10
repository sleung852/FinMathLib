#include "StockPriceModel.h"

using namespace std;

vector<double> StockPriceModel::
            generateRiskNeutralPricePath(
        double toDate,
        int nSteps ) const {
    return generatePricePath( toDate, nSteps, getRiskFreeRate() );
}

// /**
//  *  Creates a price path according to the model parameters
//  */
vector<double> StockPriceModel::generatePricePath(
        double toDate,
        int nSteps ) const {
    return generatePricePath( toDate, nSteps, getDrift() );
}


vector<double> StockPriceModel::generatePricePath(
        double toDate,
        int nSteps, 
        double rate) const {
    return vector<double>(nSteps, getStockPrice());
}