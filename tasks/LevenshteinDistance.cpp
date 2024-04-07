#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	int n = int(s1.length()), m = int(s2.length());
	vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));
	ll dc = 1, ic = 1, rc = 1;
	for (int i = 1; i < n; i++) dp[i][0] = i * dc;
	for (int j = 1; j < m; j++) dp[0][j] = j * ic;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1];
			}
			else if (s1[i - 1] != s2[j - 1]) {
				dp[i][j] = min(dp[i][j - 1] + ic, 
					min(dp[i - 1][j] + dc, dp[i - 1][j - 1] + rc));
			}
		}
	}
	cout << dp[n][m];
	return 0;
}
