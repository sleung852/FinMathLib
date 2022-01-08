#include "stdafx.h"
#include "testing.h"
using namespace std;




void testUninitialisedArray() {
    // Create an unintialised of length 5
    int myArray[5];
    for (int i=0; i<5; i++) {
        cout<<"Entry "<<i<<"=";
        cout<<myArray[i];
        cout<<"\n";
    }
}

void testInitialisedArray() {
    // Create an initialised array
    int myArray[] = {1, 1, 2, 3, 5};
    for (int i=0; i<5; i++) {
        cout<<"Entry "<<i<<"=";
        cout<<myArray[i];
        cout<<"\n";
    }
}

void testInitialisedWithZeroArray() {
    // Create an initialised array
    int myArray[5] = {};
    for (int i=0; i<5; i++) {
        cout<<"Entry "<<i<<"=";
        cout<<myArray[i];
        cout<<"\n";
    }
}

void testArrayLengthBiggerThanData() {
    int myArray[5] = {1,2,3};
    for (int i=0; i<5; i++) {
        cout<<"Entry "<<i<<"=";
        cout<<myArray[i];
        cout<<"\n";
    }
}



void test2DArray() {

    // Create an initialised 3x5 array
    int myArray[][5] = {{1, 2, 3, 4, 5},
                       {2, 0, 0, 0, 0},
                       {3, 0, 0, 0, 0}};
    for (int i=0; i<3; i++) {
        for (int j=0; j<5; j++) {
            cout<<"Entry ("<<i<<","<<j<<")=";
            cout<<myArray[i][j];
            cout<<"\n";
        }
    }
}


// User has to tell us the length
int sumArray( int toSum[], int length ) {
    int sum = 0;
    for (int i=0; i<length; i++) {
        sum+=toSum[i];
    }
    return sum;
}

void testUsingAnArray() {
    int n = 10;
    int tenSquares[10];
    // this doesn't work!
    // int tenSquares[n];
    for (int i=0; i<n; i++) {
        tenSquares[i] = i*i;
    }
    int sum = sumArray( tenSquares, n );
    cout<<"Sum="<<sum<<"\n";
}



void testVariableSizeData() {
    int n = 5;
    int* myArray = new int[n];
    for (int i=0; i<n; i++) {
        cout<<"Entry "<<i<<"=";
        cout << myArray[i];
        cout << "\n";
    }
    delete[] myArray;
}

void testPointerExample() {

    int myVariable = 10;
    int* pointerToMyVariable = &myVariable;

    cout << "Memory location of myVariable ";
    cout << pointerToMyVariable;
    cout << "\n";

    cout << "Value of myVariable ";
    cout << (*pointerToMyVariable);
    cout << "\n";

}


// User has to tell us the length
int sumUsingPointer( int* toSum, int length ) {
    int sum = 0;
    for (int i=0; i<length; i++) {
        sum+=toSum[i];
    }
    return sum;
}


// User has to tell us the length
int sumUsingPointerArithmetic( int* toSum,
                               int length ) {
    int sum = 0;
    for (int i=0; i<length; i++) {
		int* ithElement = toSum + i;
        int valueOfIthElement = *ithElement;
        sum+= valueOfIthElement;
    }
    return sum;
}
int sumUsingPlusPlus( int* firstElement, int n) {
    int sum = 0;
    int* pointer = firstElement;
    int* oneAfterEnd = firstElement + n;
    while (pointer!=oneAfterEnd) {
        sum += *pointer;
        pointer++;
    }
    return sum;
}

int sumUsingForAndPlusPlus(int* begin, int n) {
	int sum = 0;
	int* end = begin + n;
	for (int* ptr = begin; ptr != end; ptr++) {
        sum += *ptr;
	}
	return sum;	
}





void testUsingPointers() {
    int n = 10;
    int* nSquares = new int[n];
    for (int i=0; i<n; i++) {
        nSquares[i] = i*i;
    }
    int sum1 = sumArray( nSquares, n );
    int sum2 = sumUsingPointer( nSquares, n );
    int sum3 = sumUsingPointerArithmetic( nSquares, n );
    int sum4 = sumUsingPlusPlus( nSquares, n );
    int sum5 = sumUsingForAndPlusPlus( nSquares, n );
    cout<<"Sum1="<<sum1<<"\n";
    cout<<"Sum2="<<sum2<<"\n";
    cout<<"Sum3="<<sum3<<"\n";
    cout<<"Sum4="<<sum4<<"\n";
    cout<<"Sum5="<<sum5<<"\n";
    delete[] nSquares;
}

void testCharArray() {
    char charArray1[] =
        {'H', 'e', 'l', 'l', 'o', '\0' };
    for (int i=0; i<6; i++) {
        cout << "ASCII VALUE ";
        char c = charArray1[i];
        cout << ((int)c);
        cout << "\n";
    }

    cout << "Now use easy notation\n";

    const char* charArray2 = "Hello";
    for (int i=0; i<6; i++) {
        cout << "ASCII VALUE ";
        char c = charArray2[i];
        cout << ((int)c);
        cout << "\n";
    }
}

int computeLengthOfString( const char* s ) {
    int length = 0;
    while ((*s)!=0) {
        s++;
        length++;
    }
    return length;
}

void testComputeLengthOfString() {
    const char* quotation="To be or not to be";
    int l1 = computeLengthOfString( quotation );
    int l2 = strlen( quotation ); // built in
    ASSERT( l1==l2 );
}

class IntArray {
public:
    int* firstElement;
    int  length;
};

class FastString {
public:
    char* firstElement;
    int   length;
};

/*  Let's create an example class */
class Pair {
public:
    double x;
    double y;
    Pair();
    Pair( double x, double y );
};

Pair::Pair() :
    x(0.0), y(0.0) {
}

Pair::Pair( double x, double y ) :
    x(x), y(y) {
}


void testNewPairArray() {
    int n = 5;
    Pair* myPairs = new Pair[n];
    for (int i=0; i<n; i++) {
        double xValue = myPairs[i].x;
        double yValue = myPairs[i].y;

        cout<<"Pair (";
        cout<< xValue;
        cout<<",";
        cout<< yValue;
        cout<<")\n";
    }
    delete[] myPairs;
}

char* thisFunctionReturnsAnArray() {
    /* This produces a compiler warning */
    char text[] = "Don't do this";
    return text;
}

void someOtherFunction() {
    char text[] = "Alternative text\n";
    cout << text;
    cout << "\n";
}

void testDontReturnArrays() {
    char* text = thisFunctionReturnsAnArray();
    someOtherFunction();
    cout << text;
    cout << "\n";
}


char* thisFunctionReturnsAPointer() {
    char text[] = "This works";
    int n = strlen(text);
    char* ret = new char[n+1];
    /* We now get a compiler warning here */
    strcpy( ret, text );
    return ret;
}

void testReturnPointerJustAboutOK() {
    char* text = thisFunctionReturnsAPointer();
    someOtherFunction();
    cout << text;
    cout << "\n";
    // don't forget to free the memory
    delete[] text;
}


void testCreateObjectOnHeap() {

    Pair* myPair = new Pair;
    myPair->x = 1.3;
    myPair->y = 2.5;

    cout << "Pair (";
    cout << (myPair->x);
    cout << ", ";
    cout << (myPair->y);
    cout << ")\n";

    delete myPair;
}

void testUsingStarOperator() {

    Pair* myPair = new Pair;
    Pair& pairRef=*myPair;

    pairRef.x = 1.3;
    pairRef.y = 2.5;

    cout << "Pair (";
    cout << (pairRef.x);
    cout << ", ";
    cout << (pairRef.y);
    cout << ")\n";

    cout << "Pair (";
    cout << ((*myPair).x);
    cout << ", ";
    cout << ((*myPair).y);
    cout << ")\n";

    delete myPair;
}

void testUsingSharedPtr() {

    shared_ptr<Pair> myPair = make_shared<Pair>();
    Pair& pairRef=*myPair;

    pairRef.x = 1.3;
    pairRef.y = 2.5;

    cout << "Pair (";
    cout << (pairRef.x);
    cout << ", ";
    cout << (pairRef.y);
    cout << ")\n";

    cout << "Pair (";
    cout << ((*myPair).x);
    cout << ", ";
    cout << ((*myPair).y);
    cout << ")\n";

    //delete myPoint;
}

shared_ptr<Pair> thisFunctionReturnsASharedPointer() {
    shared_ptr<Pair> pair = make_shared<Pair>();
    pair->x = 1.3;
    pair->y = 2.5;
    return pair;
}

void testReturnSharedPointer() {

    shared_ptr<Pair> p =
        thisFunctionReturnsASharedPointer();

    cout <<"Pair (";
    cout << p->x;
    cout << ", ";
    cout << p->y;
    cout << ")\n";

    // no need to delete (phew!)
}

void testOverrunning() {
    char* shortText = new char[20];
    for (int i=0; i<1000; i++) {
        shortText[i] = 'x';
    }
    delete[] shortText;
}
void testIncorrectMemoryManagement() {
    int* a = new int[10];
    int* b = new int[20000000];
    cout << "Arrays created";
    delete[] a;
    delete[] b;
}

void testCorrectMemoryManagement() {
    bool errorOccurred = false;
    int* a = new int[10];
    try {
        int* b = new int[20000000];
        try {
            cout << "Arrays created";
        } catch (...) {
            errorOccurred = true;
        }
        delete[] b;
    } catch (...) {
        errorOccurred = true;
    }
    delete[] a;
    if (errorOccurred) {
        throw exception();
    }
}

void testArrowOperator() {
    Pair p;
    Pair* pointerToP = &p;

    // Use -> to access fields via a pointer
    pointerToP->x = 123.0;
    pointerToP->y = 456.0;

    // We check that c has changed
    ASSERT( p.x==123.0 );
    ASSERT( p.y==456.0 );

    // You could use * and .
    ASSERT( (*pointerToP).x==123.0 );
    ASSERT( (*pointerToP).y==456.0 );

}

class Instrument {
public:
    string bloombergTicker;
    string ricCode;
    string companyName;
    Instrument() {}
};

class Position {
public:
    string trader;
    double quantity;
    Instrument* instrument;
    explicit Position( Instrument * instrument );
};

Position::Position( Instrument* instrument ) :
    instrument( instrument ) {
}

vector<Position> constructPositions() {
    // the caller of this function
    // should call delete on the instrument
    // when they are done with all the positions
    vector<Position> positions;

    Instrument* instrument = new Instrument;
    instrument->companyName = "Google";
    instrument->bloombergTicker = "GOOG US Equity";
    instrument->ricCode = "GOOG.OQ";

    Position p1(instrument);
    p1.trader = "Han";
    p1.quantity = 100.00;
    positions.push_back( p1 );

    Position p2(instrument);
    p2.trader = "Leia";
    p2.quantity = -100.00;
    p2.instrument = instrument;
    positions.push_back( p2 );

    return positions;
}

void testConstructPositions() {
    vector<Position> r = constructPositions();
    int n = r.size();
    for (int i=0; i<n; i++) {
        cout << "Position "<<i<<"\n";
        Position& p=r[i];
        cout << "Trader "<<p.trader<<"\n";
        cout << "Quantity "<<p.quantity<<"\n";
        cout << "Instrument ";
        cout << p.instrument->companyName<<"\n";
        cout << "\n";
    }
    delete r[0].instrument;
}
string getCompanyName( Position& position ) {
    if (position.instrument==nullptr) {
        return "Name not set";
    } else {
        return position.instrument->companyName;
    }
}

class PositionV2 {
public:
    string trader;
    double quantity;
    shared_ptr<Instrument> instrument;
    explicit PositionV2(shared_ptr<Instrument> ins );
};

PositionV2::PositionV2(shared_ptr<Instrument> ins ) :
    instrument( ins ) {
}

vector<PositionV2> constructPositionsV2() {
    vector<PositionV2> positions;

	shared_ptr<Instrument> ins
		= make_shared<Instrument>();
    ins->companyName = "Google";
    ins->bloombergTicker = "GOOG US Equity";
    ins->ricCode = "GOOG.OQ";

    PositionV2 p1(ins);
    p1.trader = "Han";
    p1.quantity = 100.00;
    positions.push_back( p1 );

    PositionV2 p2(ins);
    p2.trader = "Leia";
    p2.quantity = -100.00;
    p2.instrument = ins;
    positions.push_back( p2 );

    return positions;
}


void testConstructPositionsV2() {
    vector<PositionV2> r = constructPositionsV2();
    int n = r.size();
    for (int i=0; i<n; i++) {
        cout << "Position "<<i<<"\n";
        PositionV2& p=r[i];
        cout << "Trader "<<p.trader<<"\n";
        cout << "Quantity "<<p.quantity<<"\n";
        cout << "Instrument ";
        cout << p.instrument->companyName<<"\n";
        cout << "\n";
    }
}

class PositionV3 {
public:
    string trader;
    double quantity;
    Instrument& instrument;
    explicit PositionV3( Instrument& instrument );
};

PositionV3::PositionV3( Instrument& instrument ) :
    instrument(instrument) {
}

PositionV3 constructPositionV3() {
    // This function doesn't work, the instrument
    // is deleted, so all the returned positions
	// contain broken references
    vector<PositionV3> positions;

    Instrument instrument;
    instrument.companyName = "Google";
    instrument.bloombergTicker = "GOOG US Equity";
    instrument.ricCode = "GOOG.OQ";

    PositionV3 position(instrument);
    position.trader = "Han";
    position.quantity = 100.00;
    return position;
}
void testConstructPositionV3() {
    // This will fail horribly
    PositionV3 p = constructPositionV3();
    cout << "Trader "<<p.trader<<"\n";
    cout << "Quantity "<<p.quantity<<"\n";
    cout << "Instrument ";
    cout << p.instrument.companyName<<"\n";
    cout << "\n";
}

class RealFunction {
public:
    ~RealFunction() {};
    virtual double evaluate( double x )=0;
};

double integral( RealFunction& f, double a, double b, int nSteps ) {
    double h = (b-a)/nSteps;
    double s = a + h/2;
    double total = 0;
    for (int i=0; i<nSteps; i++) {
        total+=h*f.evaluate(s);
        s+=h;
    }
    return total;
}

double integralToInfinity(RealFunction& f,
	double lowerLimit, int nPoints) {

    class DefiniteIntegrand : public RealFunction {
    public:
        RealFunction& g;
        double lowerLimit;

        DefiniteIntegrand(RealFunction& g,
                          double lowerLimit) :
            g(g), lowerLimit(lowerLimit) {
        }

        double evaluate(double x) {
            return (1/(x*x))
                * g.evaluate(lowerLimit - 1 + (1/x));
        }
    };

    DefiniteIntegrand integrand(f, lowerLimit);
    return integral(integrand, 0, 1, nPoints);
}
double cStyleIntegrate( double (*f)(double),
                        double a, double b,
                        int nSteps  ) {
    double h = (b-a)/nSteps;
    double s = a + h/2;
    double total = 0;
    for (int i=0; i<nSteps; i++) {
        total+=h*f(s);
        s+=h;
    }
    return total;
}
void testCStyleIntegrate() {
  double value = cStyleIntegrate( &sin, 0, 1, 1000);
  ASSERT_APPROX_EQUAL(value,-cos(1.0)+cos(0.0),0.0001);
}

/**
 *  A void* points to potentially any data,
 *  A void** is an array of pointers of unspecified type
 *  This will reverse the order of such an array
 */
void reverse( void* memArray,
              int length,
              size_t sizeOfElement ) {
    char* asChar = (char*)memArray;
    char* temp = new char[length*sizeOfElement];
    memcpy( temp, memArray, length*sizeOfElement );
    for (int i=0; i<length; i++) {
        memcpy( asChar + i*sizeOfElement,
                temp + (length-i-1)*sizeOfElement,
                sizeOfElement );
    }
    delete[] temp;
}

void testReverse() {
    char* s1 = "The rain in Spain";
    char* s2 = "falls mainly in";
    char* s3 = "the plains";
    char* sArray[] = {s1,s2,s3};
    reverse( sArray, 3, sizeof(char*) );
    for (int i=0; i<3; i++) {
        cout << sArray[i] << "\n";
    }

    double dArray[] = {1.0, 2.0, 3.0};
    reverse( dArray, 3, sizeof( double ));
    for (int i=0; i<3; i++) {
        cout << dArray[i] << "\n";
    }
}

void polarToCartesian(double r, double theta,
	double* x, double* y) {
	*x = r*cos(theta);
	*y = r*sin(theta);
}

void testPolarToCartesian() {
	double r = 2;
	double theta = atan(1);
	double x;
	double y;
	polarToCartesian(r, theta, &x, &y);
	ASSERT_APPROX_EQUAL(x, sqrt(2), 0.0001);
	ASSERT_APPROX_EQUAL(y, sqrt(2), 0.0001);
}



void constPointerExamples() {
	const char* ptr = "A string";
	ptr++;
	std::cout << (*ptr);
	// (*ptr)='a';  // You can't change the data
	// using a const char*

	char* fiveChars = new char[5];
	char *const constPtr = fiveChars;
	// constPtr++;  // You can't change a char *const
	(*constPtr) = 'h'; // but you can change
	                   // what it points to
}
void fivePrimes() {
	int* fivePrimes = new int[5];
	fivePrimes[0] = 2;
	fivePrimes[1] = 3;
	fivePrimes[2] = 5;
	fivePrimes[3] = 7;
	fivePrimes[4] = 11;
}

/*
10.8.1
Write a function sumDoubles which takes a pointer to a list of doubles and the length of the list and returns the total.
Write a test for this function.
*/
double sumDoubles(double list[], int size) {
    double sum = 0;
    for (size_t i=0; i<size; i++) {
        sum += list[i];
    }
    return sum;
}
// Test
static void testSumDoubles() {
    double list[] = {1,2,3,4,5};
    ASSERT_APPROX_EQUAL(sumDoubles(list, 5), 15, 0.01);
}

/*
10.8.2
Write a function reverseDoubles which takes a pointer to a list of doubles and the length of the list and reverses it.
So (1,2,3,4) should be changed to (4, 3, 2, 1), for example. Write a test for this function.
*/

void reverseDoubles(double list[], int size){
    double temp[size];
    for (size_t i=0; i<size; i++) {
        temp[i] = list[size-i-1];
    }
    for (size_t i=0; i<size; i++) {
        list[i] = temp[i];
    }
}
// Test
static void testReverseDoubles() {
    double list[] = {1,2,3,4,5};
    double target[] = {5,4,3,2,1};
    reverseDoubles(list, 5);
    for (size_t i=0; i<5; i++) {
        ASSERT (list[i]==target[i]);
    }
}

/*
Write a function meanDistance which takes a pointer to a list of Pair objects
and computes the mean distance of (x, y) to the origin.
*/

double meanDistance(Pair pairArray[], int size) {
    double distancesSum = 0;
    for (size_t i=0; i<size; i++) {
        double x = pairArray[i].x;
        double y = pairArray[i].y;
        distancesSum += sqrt(x*x + y*y);
    }
    return distancesSum/size;
}

/*
Write a function polarToCartesian which takes four parameters: r, theta, x, and y. x and y should be passed by pointers.
The function should populate the values pointed to by x and y with the r cos(θ) and r sin(θ). Write a test for this function.
*/

void polarToCartesianV2(double r, double theta, double* x, double* y) {
    *x = r * cos(theta);
    *y = r * sin(theta);
}

// test

static void testPolarToCartesianV2() {
    double r = 10;
    double theta = 0.5;
    double* x = new double;
    double* y = new double;
    polarToCartesianV2(r, theta, x, y);
    Pair pairList[] = {Pair(*x, *y)};
    double dist = meanDistance(pairList, 1);
    delete x;
    delete y;
    ASSERT_APPROX_EQUAL(dist, r, 0.01);
}

/*
Write a function reverseString which takes a char* string and re- verses it.
This should be similar to your reverseDoubles function except you need to consider the terminating zero.
Write a test for your function.
*/

void reverseString(char* str) {
    int size = strlen(str);
    char temp[size];
    for (size_t i=0; i<size; i++) {
        temp[i] = str[size-1-i];
    }
    for (size_t i=0; i<size; i++) {
        str[i] = temp[i];
    }
}

static void testReversestring(){
    char str[] = "ABCD";
    char tar[] = "DCBA";
    reverseString(str);
    for (size_t i=0; i<4; i++) {
        stringstream ss;
        ss << "Target[" << i << "]: " << str[i] << " | Expected[" << i << "]: " << tar[i];
        DEBUG_PRINT(ss.str());
        ASSERT (str[i] == tar[i]);
    }
}

/*
Write a function concatenate to append one null-terminated string to another.
I’ve deliberately not told you the parameters or return type, this is a design question for you to solve.
When you have come up with your own solution, take a look at the standard library functions
strcat and strcat_s to see how others have solved this problem.
Of course, you should use the library functions rather than write your own.
*/

void concatentate(char* first, char* second, char* output) {
    size_t counter=0;
    for (size_t i=0; i<strlen(first); i++) {
        output[counter] = first[i];
        counter++;
    }
    for (size_t i=0; i<strlen(second); i++) {
        output[counter] = second[i];
        counter++;
    }
}

/*
Write a function search which takes as input two char* strings.
The first should be phrase, a phrase to search for, the second should be text, some text to scan through.
It should return the number of times phrase appears in text. So search("be","to␣be␣or␣not␣to␣be") should return "2".
*/

int search(char* phrase, char* text) {
    int count = 0;
    int phraseLength = strlen(phrase);
    int textLength = strlen(text);

    for (size_t i=0; i<textLength; i++) {
        bool flag = true;
        // cout << "Phase " << i << endl;
        for (size_t j=0; j<phraseLength; j++) {
            // cout << "Comparing (phrase) " << phrase[j] << " with (text) " << text[i+j] << endl;
            if (phrase[j]!=text[i+j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            // cout << "Found!" << endl;
            count++;
        }
    }
    return count;
}

static void testSearch() {
    char phrase[] = "be";
    char text[] = "to be or not to be";
    DEBUG_PRINT(search(phrase, text));
    ASSERT (search(phrase, text) == 2);
}

int main() {
    TEST( testUninitialisedArray );
    TEST( testInitialisedArray );
    TEST( testInitialisedWithZeroArray );
    TEST( testArrayLengthBiggerThanData );
    TEST( test2DArray );
    TEST( testUsingAnArray );
    TEST( testVariableSizeData );
    TEST( testPointerExample );
    TEST( testUsingPointers );
    TEST( testCharArray );
    TEST( testComputeLengthOfString );
    TEST( testNewPairArray );
    TEST( testReturnPointerJustAboutOK );
    TEST( testCreateObjectOnHeap );
    TEST( testUsingStarOperator );
    TEST( testCorrectMemoryManagement );
    TEST( testArrowOperator );
    TEST( testConstructPositions );
    TEST( testConstructPositionsV2 );
    TEST( testCStyleIntegrate );
    TEST( testReverse );
	TEST(testPolarToCartesian);

    //TEST( testDontReturnArrays );
    //TEST( testOverrunning );
    //TEST( testConstructPositionV3 );

    TEST ( testSumDoubles );
    TEST (testReverseDoubles);
    TEST (testPolarToCartesianV2);
    // setDebugEnabled(true);
    TEST (testReversestring);
    // setDebugEnabled(false);

    setDebugEnabled(true);
    TEST (testSearch);
    setDebugEnabled(false);

    char strA[] = "apple";
    char strB[] = " pie";
    char strC[10];
    concatentate(strA, strB, strC);
    for (size_t i=0; i<strlen(strC); i++) {
        cout << strC[i];
    }
    cout << endl;

    // cout << "Count: " << strlen("ABC") << endl;


    return 0;
}


