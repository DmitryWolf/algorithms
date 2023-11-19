#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;
const long long MOD = 1e9 + 7;

namespace combinatorics {
    long long binPow(long long x, long long p, long long mod = MOD) {
        if (!p)
            return 1;
        if (p % 2)
            return binPow(x, p - 1, mod) * x % mod;
        long long r = binPow(x, p / 2, mod);
        return r * r % mod;
    }

    vector<long long> precalcFactorials() {
        vector<long long> memo(1e5);
        memo[0] = 1;
        for (int i = 1; i < memo.size(); i++)
            memo[i] = memo[i - 1] * i % MOD;
        return memo;
    }
    long long factorial(int n) {
        static vector<long long> memo = precalcFactorials();
        return memo[n];
    }
    long long invBP(long long x) {
        return binPow(x, MOD - 2, MOD);
    }
    long long c(int n, int k) {
        return factorial(n) * invBP(factorial(k)) % MOD * invBP(factorial(n - k)) % MOD;
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
