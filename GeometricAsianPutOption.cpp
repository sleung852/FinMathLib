#include "GeometricAsianPutOption.h"
#include "matlib.h"

Matrix GeometricAsianPutOption::payoff(const Matrix &prices) const {
  // TODO: implement when have time, along geoMean in matlib
  Matrix payoff;
  return payoff;
}

double GeometricAsianPutOption::price(const MultiStockModel &msm) const {
  BlackScholesModel bsm = msm.getBlackScholesModel(getStock());
  double S = bsm.stockPrice;
  double K = getStrike();
  double sigma = bsm.volatility;
  double r = bsm.riskFreeRate;
  double T = getMaturity() - bsm.date;

  double n = 1;
  double sigmaHat = sigma * sqrt((n + 1) * (2 * n + 1) / (6 * n * n));
  double muHat =
      (r - 0.5 * sigma * sigma) * (n + 1) / (2 * n) + 0.5 * sigmaHat * sigmaHat;

  double numerator = log(S / K) + (r + sigmaHat * sigmaHat * 0.5) * T;
  double denominator = sigmaHat * sqrt(T);
  double d1Hat = numerator / denominator;
  double d2Hat = d1Hat - denominator;
  return exp(-r * T) *
         (K * normcdf(-d2Hat) - exp(-muHat * T) * S * normcdf(-d1Hat));
}