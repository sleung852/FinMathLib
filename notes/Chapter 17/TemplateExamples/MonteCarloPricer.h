#pragma once

/*
 *   Option must be an option with a payoff function
 *   and a member maturity. Model must have a function
 *   generateRiskNeutralPricePath
 */
template <typename Option, typename Model>
double monteCarloPrice(
		const Option& option,
		const Model& model,
		int nScenarios = 10000) {
	double total = 0.0;
	for (int i = 0; i<nScenarios; i++) {
		std::vector<double> path = model.
			generateRiskNeutralPricePath(
			option.maturity,
			1);
		double stockPrice = path.back();
		double payoff = option.payoff(stockPrice);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = model.riskFreeRate;
	double T = option.maturity - model.date;
	return exp(-r*T)*mean;
}