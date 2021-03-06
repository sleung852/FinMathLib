#pragma once

#include "stdafx.h"
#include "Priceable.h"
#include "ContinuousTimeOption.h"

/**
 *   A Portfolio contains options in various quantities
 */
class Portfolio : public Priceable {
public:
    /*  Virtual destructor */
    virtual ~Portfolio() {};
    /*  Returns the number of items in the portflio */
    virtual int size() const = 0;
    /*  Add a new security to the portfolio, returns the index
        at which it was added */
    virtual int add( double quantity,
             std::shared_ptr<ContinuousTimeOption> security ) = 0;
    /*  Update the quantity at a given index */
    virtual void setQuantity( int index,
                              double quantity ) = 0;
    /*  Compute the current price */
    virtual double price( const MultiStockModel& model )
                              const = 0;
    /*  Compute prices by grouping same maturity options together */
    virtual double priceByMonteCarlo( const MultiStockModel& model ) const=0;

    /*  Creates a Portfolio */
    static std::shared_ptr<Portfolio> newInstance();
};

void testPortfolio();