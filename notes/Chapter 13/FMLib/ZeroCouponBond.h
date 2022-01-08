#ifndef B3C11F8A_EBAA_4F0F_9F4D_B46AE1229C37
#define B3C11F8A_EBAA_4F0F_9F4D_B46AE1229C37

#include "stdafx.h"
#include "Priceable.h"

class ZeroCouponBond : public Priceable {
    public:
        double price(const BlackScholesModel& model) const;

        void setExpiry(double expiry_in) {
            expiry = expiry_in;
        }

        double getExpiry() {
            return expiry;
        }
        
    private:
        double expiry;

};

#endif /* B3C11F8A_EBAA_4F0F_9F4D_B46AE1229C37 */
