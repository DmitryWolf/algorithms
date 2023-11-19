#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

vector<int> zFunction(const string &s) {
    vector<int> z(s.size());

    int blockL = 0, blockR = 0;
    for (int i = 1; i < s.size(); i++) {
        int blockLen = 0;

        if (i <= blockR)
            blockLen = min(z[i - blockL], blockR - i + 1);

        while (i + blockLen <= s.size() && s[i + blockLen] == s[blockLen])
            blockLen++;

        z[i] = blockLen;

        if (blockR < i + blockLen - 1) {
            blockL = i;
            blockR = i + blockLen - 1;
        }
    }

    return z;
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
