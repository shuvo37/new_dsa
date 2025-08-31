
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100000; // Adjust the maximum value as needed

vector<vector<int>> divisors(MAX_N + 1);

// Precompute divisors for all numbers from 1 to MAX_N
void precomputeDivisors() {
    for (int i = 1; i <= MAX_N; i++) {
        for (int j = i; j <= MAX_N; j += i) {
            divisors[j].push_back(i); // i is a divisor of j
        }
    }
}

int main() {
    precomputeDivisors();

    int n = 10; // Show divisors for numbers 1 to 10
    for (int i = 1; i <= n; i++) {
        cout << "Divisors of " << i << ": ";
        for (int d : divisors[i]) {
            cout << d << " ";
        }
        cout << endl;
    }

    return 0;
}
