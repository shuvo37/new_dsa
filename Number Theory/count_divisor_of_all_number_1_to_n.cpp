
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000;

vector<int> divisorCount(MAX_N + 1, 0);

// Precompute number of divisors for all numbers from 1 to MAX_N
void precomputeDivisorCount() {
    for (int i = 1; i <= MAX_N; i++) {
        for (int j = i; j <= MAX_N; j += i) {
            divisorCount[j]++; // Increment divisor count for j
        }
    }
}

int main() {
    precomputeDivisorCount();

    int n = 10;
    for (int i = 1; i <= n; i++) {
        cout << "Number of divisors of " << i << ": " << divisorCount[i] << endl;
    }

    return 0;
}
