#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;
const long long MOD = 1e9 + 7;

class ModInt {
    long long value;
    static long long gcdex(long long a, long long b, long long& x, long long& y) {
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

public:
    ModInt(long long value = 0) : value((value% MOD + MOD) % MOD) {}

    ModInt operator + (const ModInt& that) const {
        return value + that.value;
    }

    ModInt operator - (const ModInt& that) const {
        return value - that.value;
    }

    ModInt operator * (const ModInt& that) const {
        return value * that.value;
    }

    ModInt operator / (const ModInt& that) const {
        long long x, y;
        gcdex(that.value, MOD, x, y);
        return value * x;
    }

    bool canDivide(const ModInt& that) const {
        long long x, y;
        return that.value && gcdex(that.value, MOD, x, y) == 1;
    }

    friend istream& operator >> (istream& in, ModInt& m) {
        long long value;
        in >> value;
        m = ModInt(value);
        return in;
    }

    friend ostream& operator << (ostream& out, const ModInt& m) {
        return out << m.value;
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
