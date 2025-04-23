#include <iostream>
#include <cmath> // For std::trunc

using namespace std;

int main() {
    double value = 2.354555;
    // Multiply by 1000, truncate, and then divide by 1000.0
    double truncatedValue = std::trunc(value * 1000.0) / 1000.0;
    cout << "Truncated value: " << truncatedValue << endl; // Outputs: 2.354
    return 0;
}