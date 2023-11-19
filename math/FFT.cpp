#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

namespace FFT {
    typedef complex<double> base;
    const double PI = acos(-1);

    void fft(vector<base>& a, bool invert) {
        int n = (int)a.size();

        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1)
                j -= bit;
            j += bit;
            if (i < j)
                swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            base wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                base w(1);
                for (int j = 0; j < len / 2; ++j) {
                    base u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert)
            for (int i = 0; i < n; ++i)
                a[i] /= n;
    }


    vector<int> multiply(const vector<int>& a, const vector<int>& b) {
        vector<int> res;
        vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        size_t n = 1;
        while (n < max(a.size(), b.size()))  n <<= 1;
        n <<= 1;
        fa.resize(n), fb.resize(n);

        fft(fa, false), fft(fb, false);
        for (size_t i = 0; i < n; ++i)
            fa[i] *= fb[i];
        fft(fa, true);

        res.resize(n);
        for (size_t i = 0; i < n; ++i)
            res[i] = int(fa[i].real() + 0.5);
        return res;
    }

    vector<int> multnums(int a, int b) {
        vector<int> A, B;
        while (a) {
            A.push_back(a % 10);
            a /= 10;
        }
        while (b) {
            B.push_back(b % 10);
            b /= 10;
        }
        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());


        vector<int> res = multiply(A, B);

        int c = 0;
        for (int i = 1; i < res.size(); i++) {
            if (res[i] == 0 && res[i - 1] != 0) c = 1;
            else if (res[i] == 0 && res[i - 1] == 0) c++;
            else c = 0;
        }
        while (A.size() > 0 && A.back() == 0) { A.pop_back(); c--; }
        while (B.size() > 0 && B.back() == 0) { B.pop_back(); c--; }
        while (c--) {
            res.pop_back();
        }

        int carry = 0;
        reverse(res.begin(), res.end());
        for (size_t i = 0; i < res.size(); i++) {
            res[i] += carry;
            carry = res[i] / 10;
            res[i] %= 10;
        }
        if (carry != 0) res.push_back(carry);
        reverse(res.begin(), res.end());
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
