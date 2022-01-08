#ifndef B63C35AE_4024_438A_9C7C_7F4D4309E05E
#define B63C35AE_4024_438A_9C7C_7F4D4309E05E

#include "stdafx.h"
#include "ContinuousTimeOptionBase.h"

class AsianOption : public ContinuousTimeOptionBase {
    public:
        virtual double price(const std::vector<double>& stockPrices) const;

        // inline function
        bool isPathDependent() const {
            return true;
        }
};


#endif /* B63C35AE_4024_438A_9C7C_7F4D4309E05E */
