
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_N = 5000; // Adjust the maximum 'n' as needed
const ll MOD = 1e9 + 7; // Common modulus

ll nCr[MAX_N + 1][MAX_N + 1];

void precomputePascal() {
    // Base cases
    nCr[0][0] = 1;
    for (int n = 1; n <= MAX_N; n++) {
        nCr[n][0] = 1; // nC0 = 1
        for (int r = 1; r <= n; r++) {
            // Pascal's Identity: nCr = (n-1)C(r-1) + (n-1)Cr
            nCr[n][r] = (nCr[n-1][r-1] + nCr[n-1][r]) % MOD;
        }
    }
}

int main() {
    precomputePascal();

    int n = 5, r = 2;
    cout << "C(" << n << ", " << r << ") = " << nCr[n][r] << endl;
    // Output: C(5, 2) = 10

    return 0;
}
