#ifndef D9564A88_972A_44D8_AF79_A40D3B371360
#define D9564A88_972A_44D8_AF79_A40D3B371360

#include "stdafx.h"
#include "KnockoutOption.h"

class DownAndInOption : public KnockoutOption {
    public:
        Matrix payoff(
            const Matrix& prices ) const;
};

#endif /* D9564A88_972A_44D8_AF79_A40D3B371360 */
