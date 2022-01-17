#ifndef C54BD8C0_B058_481E_B39F_6466562886BD
#define C54BD8C0_B058_481E_B39F_6466562886BD

#include "stdafx.h"
#include "Strategy.h"

class BondsOnlyStrategy : public Strategy {
    public:
        double selectStockQuantity(double date, double assetPrice);
        Matrix selectStockQuantity(double date, Matrix assetPrice);
};


#endif /* C54BD8C0_B058_481E_B39F_6466562886BD */
