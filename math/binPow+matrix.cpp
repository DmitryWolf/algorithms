#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;
const long long MOD = 1e9 + 7;

long long binPow(long long x, long long p, long long mod = MOD) {
    if (!p)
        return 1;
    if (p % 2)
        return binPow(x, p - 1, mod) * x % mod;
    long long r = binPow(x, p / 2, mod);
    return r * r % mod;
}

// bigger, than LL
// Если x и mod взаимно просты, то binPow(x, p, mod) == binPow(x, p % phi(mod), mod), где phi — функция Эйлера.
// Если x и mod не взаимно просты, но p >= log2(mod), то binPow(x, p, mod) == binPow(x, p % phi(mod) + phi(mod), mod).
long long phi(long long n) {
    long long res = n;
    for (long long d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            while (n % d == 0)
                n /= d;
            res -= res / d;
        }
    }
    if (n > 1)
        res -= res / n;
    return res;
}

namespace matrix {
    using Matrix = vector<vector<long long>>;
    Matrix identityMatrix(int size) {
        Matrix res(size, vector<long long>(size));
        for (int i = 0; i < res.size(); i++)
            res[i][i] = 1;
        return res;
    }
    Matrix operator * (const Matrix& a, const Matrix& b) {
        Matrix res(a.size(), vector<long long>(b[0].size()));
        for (int y = 0; y < res.size(); y++)
            for (int x = 0; x < res[0].size(); x++)
                for (int i = 0; i < a[0].size(); i++)
                    res[y][x] = (res[y][x] + a[y][i] * b[i][x] % MOD) % MOD;
        return res;
    }

    Matrix pow(const Matrix& m, long long p) {
        if (!p)
            return identityMatrix(m.size());
        if (p % 2)
            return pow(m, p - 1) * m;
        Matrix r = pow(m, p / 2);
        return r * r;
    }
    // just in case
    Matrix mult(Matrix& a, Matrix& b) {
        return a * b;
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
