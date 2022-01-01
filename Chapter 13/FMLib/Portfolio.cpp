#include "Portfolio.h"
#include "CallOption.h"
#include "PutOption.h"
#include "UpAndOutOption.h"
#include "UpAndInOption.h"
#include <memory>

using namespace std;

/*  
 *  By using an abstract interface class with a factory constructor
 *  and only having the implementation in the C++ file we increase information
 *  hiding. Nobody knows about the PortfolioImpl class outside of the C++ file,
 *  so we can change it without any impact on anything else.
 */
class PortfolioImpl : public Portfolio {
public:
    /* Returns the number of items in the portfolio*/
    int size() const;    
    /*  Add a new security to the portfolio,
		returns the index at which it was added */
    int add( double quantity,
             shared_ptr<Priceable> security );
    /*  Update the quantity at a given index */
    void setQuantity( int index, double quantity );
    /*  Compute the current price */
    double price(
	    const BlackScholesModel& model ) const;    

    vector<double> quantities;
    vector< shared_ptr<Priceable> > securities;
};

int PortfolioImpl::size() const {
    return quantities.size();
}

int PortfolioImpl::add( double quantity,
            shared_ptr<Priceable> security ) {
    quantities.push_back( quantity );
    securities.push_back( security );
    return quantities.size();
}

double PortfolioImpl::price(
        const BlackScholesModel& model ) const {
    double ret = 0;
    int n = size();
    for (int i=0; i<n; i++) {
        ret += quantities[i]
               * securities[i]->price( model );
    }
    return ret;
}
void PortfolioImpl::setQuantity( int index,
        double quantity ) {
    quantities[index] = quantity;
}

/**
 *   Create a Portfolio
 */
shared_ptr<Portfolio> Portfolio::newInstance() {
    shared_ptr<Portfolio> ret=
    	make_shared<PortfolioImpl>();
    return ret;
}

/////////////////////////////
//  Tests
/////////////////////////////

static void testSingleSecurity() {
    shared_ptr<Portfolio> portfolio = Portfolio::newInstance();
    
    shared_ptr<CallOption> c=make_shared<CallOption>();
    c->setStrike(110);
    c->setMaturity(1.0);

    portfolio->add( 100, c );

    BlackScholesModel bsm;
    bsm.volatility = 0.1;
    bsm.stockPrice = 100;
    
    double unitPrice = c->price( bsm );
    double portfolioPrice = portfolio->price( bsm );
    ASSERT_APPROX_EQUAL( 100*unitPrice, portfolioPrice, 0.0001);
}

static void testPutCallParity() {
    shared_ptr<Portfolio> portfolio
        = Portfolio::newInstance();
    
    shared_ptr<CallOption> c
    	=make_shared<CallOption>();
    c->setStrike(110);
    c->setMaturity(1.0);

    shared_ptr<PutOption> p=make_shared<PutOption>();
    p->setStrike(110);
    p->setMaturity(1.0);

    portfolio->add( 100, c );
    portfolio->add( -100, p );

    BlackScholesModel bsm;
    bsm.volatility = 0.1;
    bsm.stockPrice = 100;
    bsm.riskFreeRate = 0;

    double expected =bsm.stockPrice - c->getStrike();
    double portfolioPrice = portfolio->price( bsm );
    
    ASSERT_APPROX_EQUAL(100*expected,
	    portfolioPrice,0.0001);
}

static void testKnockOutOptionsAndCallOptions() {

    shared_ptr<Portfolio> portfolioA = Portfolio::newInstance();

    shared_ptr<UpAndOutOption> upAndOutOption = make_shared<UpAndOutOption>();
    upAndOutOption->setBarrier(110);
    upAndOutOption->setStrike(120);
    upAndOutOption->setMaturity(2);

    shared_ptr<UpAndInOption> upAndInOption = make_shared<UpAndInOption>();
    upAndInOption->setBarrier(110);
    upAndInOption->setMaturity(2);
    upAndInOption->setStrike(120);

    portfolioA->add(100, upAndOutOption);
    portfolioA->add(100, upAndInOption);

    shared_ptr<Portfolio> portfolioB = Portfolio::newInstance();

    shared_ptr<CallOption> callOption = make_shared<CallOption>();
    callOption->setMaturity(2);
    callOption->setStrike(120);

    portfolioB->add(100, callOption);

    BlackScholesModel bsm;
    bsm.date = 1.0;
    bsm.volatility = 0.1;
    bsm.riskFreeRate = 0.05;
    bsm.stockPrice = 100.0;

    double portfolioAPrice = portfolioA->price(bsm);
    double portfolioBPrice = portfolioB->price(bsm);

    // not very accurate though
    ASSERT_APPROX_EQUAL(portfolioAPrice, portfolioBPrice, 1);
}

void testPortfolio() {
    TEST( testSingleSecurity );
    TEST( testPutCallParity );
    TEST( testKnockOutOptionsAndCallOptions);
}

