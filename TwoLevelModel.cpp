// #include "TwoLevelModel.h"
// #include "BlackScholesModel.h"

// using namespace std;

// #include "matlib.h"

// TwoLevelModel::TwoLevelModel() {
//     setDrift(0.0);
//     setStockPrice(0.0);
//     setVolatility(0.0);
//     setVolatility2(0.0);
//     setRiskFreeRate(0.0);
//     setDate(0.0);
// }

// /**
//  *  Creates a price path according to the model parameters
//  */
// vector<double> TwoLevelModel::
//             generateRiskNeutralPricePath(
//         double toDate,
//         int nSteps ) const {
//     return generatePricePath( toDate, nSteps, getRiskFreeRate() );
// }

// /**
//  *  Creates a price path according to the model parameters
//  */
// vector<double> TwoLevelModel::generatePricePath(
//         double toDate,
//         int nSteps ) const {
//     return generatePricePath( toDate, nSteps, getDrift() );
// }


// /**
//  *  Creates a price path according to the model parameters
//  */
// vector<double> TwoLevelModel::generatePricePath(
//         double toDate,
//         int nSteps,
//         double drift ) const {
//     vector<double> path(nSteps,0.0);
//     vector<double> epsilon = randn( nSteps );
//     double dt = (toDate-getDate())/nSteps;
//     double a = (drift - getVolatility()*getVolatility()*0.5)*dt;
//     double b = getVolatility()*sqrt(dt);
//     double currentLogS = log( getStockPrice() );
//     double dLogS, logS;
//     for (int i=0; i<nSteps/2; i++) {
//         dLogS = a + b*epsilon[i];
//         logS = currentLogS + dLogS;
//         path[i] = exp( logS );
//         currentLogS = logS;
//     }
//     a = (drift - getVolatility2()*getVolatility2()*0.5)*dt;
//     b = getVolatility2()*sqrt(dt);
//     for (int i=nSteps/2; i<nSteps; i++) {
//         dLogS = a + b*epsilon[i];
//         logS = currentLogS + dLogS;
//         path[i] = exp( logS );
//         currentLogS = logS;
//     }
//     return path;
// }

// ////////////////////////////////
// //
// //   TESTS
// //
// ////////////////////////////////

// void testAgainstBSM() {
//     rng("default");

//     BlackScholesModel bsm;
//     bsm.setRiskFreeRate(0.05);
//     bsm.setVolatility(0.1);
//     bsm.setStockPrice(100.0);
//     bsm.setDate(2.0);

//     int nPaths = 10000;
//     int nsteps = 5;
//     double maturity = 4.0;
//     vector<double> finalPricesBSM(nPaths,0.0);
//     for (int i=0; i<nPaths; i++) {
//         vector<double> path =
//             bsm.generateRiskNeutralPricePath( maturity,
//                                               nsteps );
//         finalPricesBSM[i] = path.back();
//     }
//     double bsmMeanPrice = mean( finalPricesBSM );

//     TwoLevelModel tlm;
//     tlm.setRiskFreeRate(0.05);
//     tlm.setVolatility(0.1);
//     tlm.setVolatility2(0.1);
//     tlm.setStockPrice(100.0);
//     tlm.setDate(2.0);
//     vector<double> finalPricesTLM(nPaths,0.0);
//     for (int i=0; i<nPaths; i++) {
//         vector<double> path =
//             bsm.generateRiskNeutralPricePath( maturity,
//                                               nsteps );
//         finalPricesTLM[i] = path.back();
//     }
//     double tlmMeanPrice = mean( finalPricesTLM );
//     ASSERT_APPROX_EQUAL( tlmMeanPrice, bsmMeanPrice, 0.5);
// }


// void testTwoLevelModel() {
//     TEST( testAgainstBSM );
// }

