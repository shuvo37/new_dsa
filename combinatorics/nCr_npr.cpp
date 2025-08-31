#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAX_N = 1000000; // Can go up to 1e6 or more
const ll MOD = 1e9 + 7;

vector<ll> fact(MAX_N + 1);
vector<ll> inv_fact(MAX_N + 1);

// Helper function for modular exponentiation
ll powmod(ll base, ll exp, ll mod) {
    base %= mod;
    ll res = 1;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials up to MAX_N
void precomputeFactorials() {
    fact[0] = 1;
    for (int i = 1; i <= MAX_N; i++) {
        fact[i] = (fact[i-1] * i) % MOD;
    }

    // Precompute all inverse factorials using Fermat's Little Theorem
    inv_fact[MAX_N] = powmod(fact[MAX_N], MOD-2, MOD);
    for (int i = MAX_N - 1; i >= 0; i--) {
        inv_fact[i] = (inv_fact[i+1] * (i+1)) % MOD;
    }
}

// Function to get nCr in O(1) time
ll nCr_query(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
}

// Function to get nPr in O(1) time
// nPr = n! / (n - r)!
ll nPr_query(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[n - r] % MOD;
}

int main() {
    precomputeFactorials(); // Call this once at the start of the program

    // Answer nCr queries in O(1)
    cout << "C(1000, 500) = " << nCr_query(1000, 500) << endl;
    cout << "C(10, 3) = " << nCr_query(10, 3) << endl;

    // Answer nPr queries in O(1)
    cout << "P(10, 3) = " << nPr_query(10, 3) << endl;
    cout << "P(5, 2) = " << nPr_query(5, 2) << endl;
    cout << "P(7, 0) = " << nPr_query(7, 0) << endl; // Should be 1

    return 0;
}
