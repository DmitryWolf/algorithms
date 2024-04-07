#include <bits/stdc++.h>
#define aint(a) (a).begin(), (a).end()
#define ull unsigned long long
#define ll long long
#define ld long double
#define PI 3.14159265358979323846
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;



class BigInt {
private:
    string s_;
public:
    BigInt() { s_ = ""; }
    BigInt(string s) { reverse(s.begin(), s.end()); s_ = s; }
    void sum(BigInt sec) {
        string s = "";
        while (s_.size() < sec.s_.size()) s_ += "0";
        while (sec.s_.size() < s_.size()) sec.s_ += "0";
        int ost = 0, temp = 0;;
        for (int i = 0; i < s_.size(); i++) {
            temp = s_[i] - 48 + sec.s_[i] - 48 + ost;
            if (temp > 9) {
                s += (temp % 10 + 48);
                ost = 1;
            }
            else {
                s += (temp + 48);
                ost = 0;
            }
        }
        if (ost == 1) {
            s += "1";
        }
        s_ = s;
    }
    BigInt operator +=(BigInt& sec) {
        this->sum(sec);
        return *this;
    }
    BigInt operator =(string& sec) {
        this->s_ = sec;
        return *this;
    }
    string Get() {
        string s = s_;
        reverse(s.begin(), s.end());
        return s;
    }
    void Set(string& s) {
        reverse(s.begin(), s.end());
        s_ = s;
    }
};

int n, m;
vector<vector<BigInt>> dp;
void f(const int& i, const int& j) {
    if (i + 2 < n && j + 1 < m) { // 2 низ, 1 право
        dp[i + 2][j + 1] += dp[i][j];
    }
    if (i + 2 < n && j - 1 >= 0) { // 2 низ, 1 лево
        dp[i + 2][j - 1] += dp[i][j];
    }
    if (i + 1 < n && j + 2 < m) { // 1 низ, 2 право
        dp[i + 1][j + 2] += dp[i][j];
    }
    if (i - 1 >= 0 && j + 2 < m) { // 1 верх, 2 право
        dp[i - 1][j + 2] += dp[i][j];
    }
}
int main() {
    IOS;
    cin >> n >> m;
    dp.resize(n, vector<BigInt>(m));
    string s1 = "1";
    dp[0][0] = s1;
    pair<int, int> beg, tmp;
    for (int j = 0; j < m; j++) {
        tmp = { 0, j };
        while (true) {
            if (tmp.first >= n || tmp.second < 0) break;
            f(tmp.first, tmp.second);
            tmp.first++; tmp.second--;
        }
    }
    for (int i = 1; i < n; i++) {
        tmp = { i, m - 1 };
        while (true) {
            if (tmp.first >= n || tmp.second < 0) break;
            f(tmp.first, tmp.second);
            tmp.first++; tmp.second--;
        }
    }
    if (dp[n - 1][m - 1].Get() == "") cout << 0;
    else cout << dp[n - 1][m - 1].Get();
}
