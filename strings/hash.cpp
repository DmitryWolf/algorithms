#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

struct Hasher {
    long long x = 31, xi = 129032259, mod = 1e9 + 7;
    vector<long long> p, pi, h;

    Hasher(const string &s) {
        p.resize(s.size());
        pi.resize(s.size());
        h.resize(s.size());

        p[0] = pi[0] = 1;
        h[0] = s[0] - 'a' + 1;

        for (int i = 1; i < s.size(); i++) {
            p[i] = p[i - 1] * x % mod;
            pi[i] = pi[i - 1] * xi % mod;
            h[i] = (h[i - 1] + p[i] * (s[i] - 'a' + 1) % mod) % mod;
        }
    }

    long long getHash(int l, int r) {
        long long res = h[r];
        if (l) {
            res = (res - h[l - 1] + mod) % mod;
            res = (res * pi[l]) % mod;
        }
        return res;
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
