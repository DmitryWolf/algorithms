#include <bits/stdc++.h>

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;

typedef long long ll;
class SparseTable {
private:
    vector<int> lg;
    vector<vector<int>> st;

public:
    SparseTable(vector<int>& a) {
        lg.resize(a.size() + 1);
        for (int i = 2; i <= a.size(); i++)
            lg[i] = lg[i / 2] + 1;

        st.push_back(a);
        for (int level = 1, levelWidth = 2; levelWidth <= a.size(); level++, levelWidth *= 2) {
            st.emplace_back();
            for (int i = 0; i + levelWidth <= a.size(); i++)
                st[level].push_back(min(st[level - 1][i], st[level - 1][i + levelWidth / 2]));
        }
    }

    int getMin(int l, int r) {
        int level = lg[r - l + 1], levelWidth = 1 << level;
        return min(st[level][l], st[level][r - levelWidth + 1]);
    }
};

ll solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SparseTable table(a);

    // first test
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int temp1 = table.getMin(i, j), temp2 = numeric_limits<int>::max();
            for (int k = i; k <= j; k++) {
                temp2 = min(temp2, a[k]);
            }
            assert(temp1 == temp2);
        }
    }
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
