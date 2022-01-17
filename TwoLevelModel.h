// #ifndef BC35C037_6619_4D79_A531_A6E1CA2761F5
// #define BC35C037_6619_4D79_A531_A6E1CA2761F5

// #include "stdafx.h"
// #include "StockPriceModel.h"

// class TwoLevelModel : public StockPriceModel {
//     public:
//         TwoLevelModel();

//         double getVolatility2() const {
//             return volatility2;
//         }

//         void setVolatility2(double volatility) {
//             this->volatility2 = volatility;
//         }

//         std::vector<double> generatePricePath(
//                                 double toDate,
//                                 int nSteps) const;

//         std::vector<double> generateRiskNeutralPricePath(
//                                 double toDate,
//                                 int nSteps) const;

//     private:
//         std::vector<double> generatePricePath(
//                                 double toDate,
//                                 int nSteps,
//                                 double drift) const;

//         double volatility2;
// };

// void testTwoLevelModel();

// #endif /* BC35C037_6619_4D79_A531_A6E1CA2761F5 */
