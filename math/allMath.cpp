#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

namespace Math {
    const long long MOD = 1e9 + 7;


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
    namespace combinatorics{
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







    

    // O(sqrt(N))
    bool isPrime(int n) {
        if (n < 2)
            return 0;
        for (long long d = 2; d * d <= n; d++)
            if (n % d == 0)
                return 0;
        return 1;
    }

    // O(sqrt(N))
    vector<int> getPrimeDivisors(int n) {
        vector<int> primeDivisors;
        for (long long d = 2; d * d <= n; d++) {
            if (n % d == 0) {
                primeDivisors.push_back(d);
                while (n % d == 0)
                    n /= d;
            }
        }
        if (n != 1)
            primeDivisors.push_back(n);
        return primeDivisors;
    }

    // O(sqrt(N))
    vector<int> factorize(int n) {
        vector<int> factorization;
        for (long long d = 2; d * d <= n; d++) {
            while (n % d == 0) {
                factorization.push_back(d);
                n /= d;
            }
        }
        if (n != 1)
            factorization.push_back(n);
        return factorization;
    }

    // O(N)
    vector<int> getPrimes(int n) {
        vector<int> minDivisor(n + 1), primes;
        for (int i = 2; i < minDivisor.size(); i++) {
            if (!minDivisor[i]) {
                minDivisor[i] = i;
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size() && primes[j] <= minDivisor[i] && 1LL * i * primes[j] < minDivisor.size(); j++)
                minDivisor[i * primes[j]] = primes[j];
        }
        return primes;
    }

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
