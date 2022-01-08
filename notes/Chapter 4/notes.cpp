#include <stdexcept>
#include <iostream>

double debitAccount(double balance, double amount) {
    double newAmount = balance - amount;
    if (newAmount < 0.0) {
        throw std::logic_error("Insufficient Fund!");
    }
    return newAmount;
}



int main() {

    // * Throw Exceptions*
    // 1. simple demonstration
    // throw std::logic_error("You cannot do this!");

    // 2. simple example
    // double balance = debitAccount(100,102);
    // std::cout << "New balance: " << balance << std::endl;

    // * Ternary Operator *
    // <test expression> ? <value if true> : <value if false>
    // 1. simple demonstration
    // (100 > 90) ? std::cout << 1 << std::endl : std::cout << 0 << std::endl; // print 1
    // (70 > 90) ? std::cout << 1 << std::endl : std::cout << 0 << std::endl; // print 0

    // * Comma Operator *
    // lhs, rhs -> evaluates lhs and dsicards the result then evaluates rhs
    // 1. simple demonstration
    for (int count=0, power=1;
        count < 10;
        count++, power*=2) {
            std::cout << power << std::endl;
        }

    return 0;
}