#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;
const long long MOD = 1e9 + 7;

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
