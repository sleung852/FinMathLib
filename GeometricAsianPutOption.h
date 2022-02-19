#pragma once

#include "ContinuousTimeOptionBase.h"

/**
 *   An option with a barrier
 */
class GeometricAsianPutOption : public ContinuousTimeOptionBase {
public:
  virtual ~GeometricAsianPutOption() {}

  Matrix payoff(const Matrix &prices) const;

  /* implement the closed form formula */
  double price(const MultiStockModel &msm) const;

  bool isPathDependent() const { return true; }
};