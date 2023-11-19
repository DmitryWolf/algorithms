#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;
const long long MOD = 1e9 + 7;

namespace euclid {
    long long gcd(long long a, long long b) {
        return b ? gcd(b, a % b) : a;
    }
    long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }
    long long gcdex(long long a, long long b, long long& x, long long& y) {
        if (!b) {
            x = 1;
            y = 0;
            return a;
        }
        long long x1, y1, d = gcdex(b, a % b, x1, y1);
        x = y1;
        y = x1 - a / b * y1;
        return d;
    }
    long long inv(long long a, long long mod = MOD) {
        long long x, y;
        return a && gcdex(a, mod, x, y) == 1 ? (x % mod + mod) % mod : 0;
    }
};

ll solve() {
    return 0;
}

int main() {
    IOS;
    ll tc = 1;
    //cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
