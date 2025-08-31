#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1000000; // 10^6

vector<int> spf(MAX_N + 1); // spf[x] = smallest prime factor of x

// Precompute the Smallest Prime Factor (SPF) for all numbers up to MAX_N
void precomputeSPF() {
    // Initialize spf array
    for (int i = 0; i <= MAX_N; i++) {
        spf[i] = i; // Every number is its own smallest prime factor initially
    }

    // Mark even numbers
    for (int i = 2; i <= MAX_N; i += 2) {
        spf[i] = 2;
    }

    // Process odd numbers
    for (int i = 3; i * i <= MAX_N; i += 2) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= MAX_N; j += i) {
                if (spf[j] == j) { // If not already marked
                    spf[j] = i;
                }
            }
        }
    }
}

// Function to get prime factors using SPF (O(log n) per number)
vector<pair<int, int>> getPrimeFactors(int n) {
    vector<pair<int, int>> factors;

    while (n > 1) {
        int prime = spf[n];
        int count = 0;

        // Count how many times this prime divides n
        while (n % prime == 0) {
            count++;
            n /= prime;
        }

        factors.push_back({prime, count});
    }

    return factors;
}

// Alternative: Get factors without pair (just the primes with multiplicity)
vector<int> getPrimeFactorsSimple(int n) {
    vector<int> factors;

    while (n > 1) {
        int prime = spf[n];
        factors.push_back(prime);
        n /= prime;
    }

    return factors;
}

int main() {
    precomputeSPF(); // Call this once at the beginning

    // Test cases
    vector<int> test_numbers = {12, 36, 97, 100, 123456};

    for (int num : test_numbers) {
        cout << "Prime factors of " << num << ": ";

        vector<pair<int, int>> factors = getPrimeFactors(num);
        for (auto x : factors) {
            cout << x.first << "^" <<  x.second << " ";
        }
        cout << endl;
    }

    return 0;
}
