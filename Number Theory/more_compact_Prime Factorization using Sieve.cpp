
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000000;
vector<int> spf(MAX_N + 1);

void precomputeSPF() {
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i <= MAX_N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAX_N; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

// Very efficient factorization function
vector<int> factorize(int n) {
    vector<int> factors;
    while (n > 1) {
        factors.push_back(spf[n]);
        n /= spf[n];
    }
    return factors;
}

// Get factors with exponents
map<int, int> factorizeWithExponents(int n) {
    map<int, int> factors;
    while (n > 1) {
        factors[spf[n]]++;
        n /= spf[n];
    }
    return factors;
}

int main() {
    precomputeSPF();

    int n = 360;
    cout << "Prime factors of " << n << " (with exponents): ";
    map<int, int> factors = factorizeWithExponents(n);
    for (auto x : factors) {
        cout << x.first << "^" << x.second << " ";
    }
    cout << endl;

    cout << "All prime factors: ";
    vector<int> all_factors = factorize(n);
    for (int f : all_factors) {
        cout << f << " ";
    }
    cout << endl;

    return 0;
}
