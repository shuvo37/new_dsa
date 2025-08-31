
#include <iostream>
using namespace std;

typedef long long ll;




// The standard modular exponentiation function from above
ll power_mod_iterative(ll x, ll y, ll mod) {
    if (mod == 1) return 0;
    x %= mod;
    ll result = 1;
    while (y > 0) {
        if (y & 1) {
            result = (result * x) % mod;
        }
        y >>= 1;
        x = (x * x) % mod;
    }
    return result;
}



// Function to calculate (x^y) % mod, handles negative exponents
ll power_mod_full(ll x, ll y, ll mod) {
    if (mod == 1) return 0;
    if (y == 0) return 1;

    // Handle negative exponent
    if (y < 0) {
        // Find the modular inverse of x under mod
        // Using Fermat's Little Theorem (requires mod to be prime)
        // Alternatively, use Extended Euclidean Algorithm for a more general solution.
        x = power_mod_iterative(x, mod - 2, mod); // This works if mod is prime
        y = -y; // Make the exponent positive
    }

    // Proceed with the standard algorithm
    x %= mod;
    ll result = 1;
    while (y > 0) {
        if (y & 1) {
            result = (result * x) % mod;
        }
        y >>= 1;
        x = (x * x) % mod;
    }
    return result;
}


int main() {
    ll x = 2, y = -1, mod = 1000000007;
    // We are calculating 2^(-1) mod 1000000007, which is the inverse of 2.
    ll ans = power_mod_full(x, y, mod);
    cout << x << "^" << y << " mod " << mod << " = " << ans << endl;
    // Verification: (2 * 500000004) % 1000000007 should be 1.
    cout << "Verification: (2 * " << ans << ") % " << mod << " = " << (2 * ans) % mod << endl;
    return 0;
}
