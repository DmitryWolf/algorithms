#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll INF = 1e9;
vector<ll> LIS(vector<ll>& a) {
	ll n = a.size();
	vector<ll> d(n + 1, INF), pos(n + 1), prev(n);
	ll len = 0;
	pos[0] = -1;
	d[0] = -INF;
	for (int i = 0; i < n; i++) {
		ll j = ll(lower_bound(d.begin(), d.end(), a[i]) - d.begin());
		if (d[j - 1] < a[i] && a[i] < d[j]) {
			d[j] = a[i];
			pos[j] = i;
			prev[i] = pos[j - 1];
			len = max(len, j);
		}
	}
	vector<ll> ans;
	ll p = pos[len];
	while (p != -1) {
		ans.push_back(a[p]);
		p = prev[p];
	}
	reverse(ans.begin(), ans.end());
	return ans;
}
int main() {
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<ll> ans = LIS(a);
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i] << " ";
	}
}
