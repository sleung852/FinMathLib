#ifndef FF47FFD9_A533_41BC_A385_49BCC8887105
#define FF47FFD9_A533_41BC_A385_49BCC8887105

#include "stdafx.h"
#include "Priceable.h"

class Stock : public Priceable {
    double price(const BlackScholesModel& model) const;
};
#endif /* FF47FFD9_A533_41BC_A385_49BCC8887105 */
