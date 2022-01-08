#include "ContinuousTimeOption.h"
#include "CallOption.h"

// double impliedVolatility(const BlackScholesModel& bsm, const ContinuousTimeOption& option, double price,
//             double a, double b, double threshold)
//     {
//         auto priceFunc = [&bsm, &option] (double x) {
//             BlackScholesModel model(bsm);
//             model.volatility = x;
//             return option.price(model);
//         }
//         return bisectionRecursion(priceFunc, a, b, price, threshold);
// }