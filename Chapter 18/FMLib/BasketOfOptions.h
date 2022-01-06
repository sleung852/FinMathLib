#ifndef A452B2EC_B382_416E_8986_99A34CF1E2B5
#define A452B2EC_B382_416E_8986_99A34CF1E2B5

#include "stdafx.h"
#include "ContinuousTimeOption.h"

class BasketOfOptions : public ContinuousTimeOption {
    public:
        /* constructor that takes in options */
        BasketOfOptions(std::vector<std::shared_ptr<ContinuousTimeOption> > options,
                        std::vector<double> weights,
                        double maturity,
                        std::set<std::string> dependentStocks);

        double price(const MultiStockModel& model) const;

        double getMaturity() const {
            return maturity;
        }

        Matrix payoff(const MarketSimulation& simulation) const;

        bool isPathDependent() const {
            bool flag = false;
            for (auto option: options) {
                if (option->isPathDependent()) {
                    flag = true;
                    break;
                }
            }
            return flag;
        }

        std::set<std::string> getStocks() const {
            return stocks;
        }

    private:
        std::vector<std::shared_ptr<ContinuousTimeOption> > options;
        std::vector<double> weights;

        double maturity;
        std::set<std::string> stocks;
};

void testBasketOfOptions();

#endif /* A452B2EC_B382_416E_8986_99A34CF1E2B5 */
