#pragma once

#include "ContinuousTimeOptionBase.h"

/**
 *   An option with a barrier
 */
class GeometricAsianCallOption : public ContinuousTimeOptionBase {
public:
  virtual ~GeometricAsianCallOption() {}

  Matrix payoff(const Matrix &prices) const;

  /* implement the closed form formula */
  double price(const MultiStockModel &msm) const;

  bool isPathDependent() const { return true; }
};