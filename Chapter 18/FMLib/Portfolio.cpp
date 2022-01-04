#include "Portfolio.h"
#include "CallOption.h"
#include "PutOption.h"
#include "UpAndOutOption.h"

using namespace std;

/*  
 *  By using an abstract interface class with a factory constructor
 *  and only having the implementation in the C++ file we increase information
 *  hiding. Nobody knows about the PortfolioImpl class outside of the C++ file,
 *  so we can change it without any impact on anything else.
 */
class PortfolioImpl : public Portfolio {
public:
    /*  Returns the number of items in the portflio */
    int size() const;    
    /*  Add a new security to the portfolio, returns the index
        at which it was added */
    int add( double quantity,
		shared_ptr<ContinuousTimeOption> security);
    /*  Update the quantity at a given index */
    void setQuantity( int index, double quantity );
    /*  Compute the current price */
    double price( const MultiStockModel& model ) const;    

//private:
    vector<double> quantities;
	vector< shared_ptr<ContinuousTimeOption> > securities;
};

int PortfolioImpl::size() const {
    return quantities.size();
}

int PortfolioImpl::add( double quantity,
	shared_ptr<ContinuousTimeOption> security) {
    quantities.push_back( quantity );
    securities.push_back( security );
    return quantities.size();
}

double PortfolioImpl::price(
        const MultiStockModel& model ) const {
    double ret = 0;
    int n = size();
    for (int i=0; i<n; i++) {
        ret += quantities[i] * securities[i]->price( model );
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
    shared_ptr<Portfolio> ret=make_shared<PortfolioImpl>();
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

	MultiStockModel msm(bsm);
    
    double unitPrice = c->price( msm );
    double portfolioPrice = portfolio->price( msm );
    ASSERT_APPROX_EQUAL( 100*unitPrice, portfolioPrice, 0.0001);
}

static void testPutCallParity() {
    shared_ptr<Portfolio> portfolio
        = Portfolio::newInstance();
    
    shared_ptr<CallOption> c=make_shared<CallOption>();
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

	MultiStockModel msm(bsm);

    double expected = bsm.stockPrice - c->getStrike();
    double portfolioPrice = portfolio->price( msm );
    
    ASSERT_APPROX_EQUAL(100*expected,portfolioPrice,0.0001);

}

void testMultiStockPortfolio() {
	auto model = MultiStockModel::createTestModel();
	auto p = Portfolio::newInstance();
	auto stocks = model.getStocks();

	double q0 = 1.0;
	auto stock0 = stocks[0];
	SPUpAndOutOption o0=make_shared<UpAndOutOption>();
	o0->setStock(stock0);
	o0->setStrike(model.getStockPrice(stock0));
	o0->setBarrier(2*model.getStockPrice(stock0));
	p->add(q0,o0);
	
	double q1 = 2.0;
	auto stock1 = stocks[1];
	SPUpAndOutOption o1=make_shared<UpAndOutOption>();
	o1->setStock(stock1);
	o1->setStrike(model.getStockPrice(stock1));
	o1->setBarrier(2 * model.getStockPrice(stock1));
	p->add(q1, o1);

	double p0 = o0->price(model);
	double p1 = o1->price(model);
	double expected = q0*p0 + q1*p1;

	double actual = p->price(model);
	ASSERT_APPROX_EQUAL(expected, actual, 0.2);
}

void testPortfolio() {
    TEST( testSingleSecurity );
    TEST( testPutCallParity );
	TEST( testMultiStockPortfolio );
}

