
#include <iostream>
#include <vector>
using namespace std;

vector<int> primeFactors(int n) {
    vector<int> factors;

    // Store the number of 2s that divide n
    while (n % 2 == 0) {
        factors.push_back(2);
        n = n / 2;
    }

    // n must be odd at this point. So we can
     // skip one element (i = i + 2)
    for (int i = 3; i * i <= n; i = i + 2) {
        while (n % i == 0) {
            factors.push_back(i);
            n = n / i;
        }
    }

    // If n is a prime number greater than 2
    if (n > 2)
        factors.push_back(n);

    return factors;
}

int main() {
    int n = 18;
    vector<int> ans = primeFactors(n);

    // Print the factors stored in vector
    for (int factor : ans) {
        cout << factor << " ";
    }
    return 0;
}
