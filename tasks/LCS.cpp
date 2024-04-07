#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	int n = int(s1.length()), m = int(s2.length());
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (s1[i - 1] == s2[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else if (s1[i - 1] != s2[j - 1]) {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	if (dp[n][m] == 0) {
		return 0;
	}
	else {
		string s = "";
		int i = n, j = m;
		while (i > 0 && j > 0) {
			if (dp[i][j] == 0) {
				break;
			}
			else if (dp[i][j] == dp[i - 1][j - 1] && dp[i][j] == dp[i - 1][j] && dp[i][j] == dp[i][j - 1]) {
				i--;
				j--;
			}
			else if (dp[i - 1][j - 1] == dp[i - 1][j] && dp[i - 1][j - 1] == dp[i][j - 1]) {
				s += s1[i - 1];
				i--;
				j--;
			}
			else if (dp[i][j - 1] == dp[i][j]) {
				j--;
			}
			else if (dp[i - 1][j] == dp[i][j]) {
				i--;
			}
		}
		reverse(s.begin(), s.end());
		cout << s;
	}
	return 0;
}
