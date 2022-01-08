#ifndef C1846D15_8E04_4CC3_AA50_5D33E6575028
#define C1846D15_8E04_4CC3_AA50_5D33E6575028

#include "stdafx.h"
#include "ContinuousTimeOption.h"

class MargrabeOption : public ContinuousTimeOption {
    public:
        double getMaturity() const {
            return maturity;
        }

        Matrix payoff(const MarketSimulation& simulation) const;

        double price(const MultiStockModel& model) const;

        bool isPathDependent() const {
            return false;
        }

        std::set<std::string> getStocks() const {
            std::set<std::string> stocks({stock1, stock2});
            return stocks;
        }
    
    private:
        // need to have both since which stock is
        // which matters
        std::string stock1;
        std::string stock2;
        double maturity;

};

#endif /* C1846D15_8E04_4CC3_AA50_5D33E6575028 */
