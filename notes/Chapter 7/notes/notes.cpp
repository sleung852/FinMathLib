#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

// A. PASS BY REFERENCE AND CONST
// pass by reference and const
double sum(const vector<double> &v) {
    double total = 0.0;
    for (size_t i=0; i<v.size(); i++) {
        total += v.at(i);
    }
    return total;
}

// Pass by reference without const -> a good way to return multiple values from a function
// ie.
void polarToCartesian(double r, double theta, double &x, double &y) {
    x = r*cos(theta);
    y = r*sin(theta);
}

// B. 

// a generic output stream ostream
// an alternative approach to Polymorphism
void writeHaiku(ostream &out) { // reference not constant, because we want to adj the obj
    out << "Help!\n";
    out << "I need somebody... Help!\n";
    out << "Not just anybody... Help!\n";
}

void testWriteHaku() {
    // write to cout
    writeHaiku(cout);
    // write to file
    ofstream out;
    out.open("haiku.txt");
    writeHaiku(out);
    out.close();
}

// this explores various classes that are very useful
int main() {
    // 1. exploring vectors

    // three ways of initialisation
    vector<double> ten3s(10, 3.0);
    vector<double> copy(ten3s);
    vector<double> direct( { 1.0, 2.0, 3.0 } );



    // 2. ofstream -> Output File Stream
    ofstream out;
    out.open("myfile.txt");
    out << "First line\n";
    out << "Second line\n";
    out.close();
    // why close()
    // a. it is faster to write 100 lines in one go compare to one at a time, which is why close is needed
    // b. allows different program to use the file

    testWriteHaku();

    // 3. string -> combines char* with some helpful functions
    // a. constantly resizing string by '+' is very slow
    // ie.
    string s("");
    for (int i=0; i<10; i++) {
        s += "blah ";
    }
    cout << endl;
    // it is much faster to use 'stringstream'
    stringstream ss;
    for (int i=0; i<100; i++) {
        ss << "blah ";
    }
    string s_ss = ss.str();
    cout << endl;
    // also to test whether a function writes to ostream (ie. into a log file or even
    // something via an internet connect), you can use stringstream to test

    return 0;
}