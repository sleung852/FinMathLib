#include <iostream>
#include <cmath>

using namespace std;

int main() {
    // inputs
    double revenue;
    double costs;
    double taxRate;
    // outputs
    double grossProfit;
    double netProfit;

    cout << "Please input revenue:\n";
    cin >> revenue;
    cout << "Please input costs:\n";
    cin >> costs;
    cout << "Please input tax_rate (%):\n";
    cin >> taxRate;

    grossProfit = (revenue - costs);

    if (grossProfit > 0) {
        netProfit = grossProfit * (1-taxRate*0.01);
    } else {
        netProfit = grossProfit;
    }

    cout << "Gross Profit: " << grossProfit << endl;
    cout << "Net Profit: " << netProfit << endl;

    return 0;
}