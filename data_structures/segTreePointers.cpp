#define _CRT_SECURE_NO_WARNINGS
#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")

typedef long long ll;
typedef long double ld;
typedef vector<ld> vld;
typedef vector<vld> vld2;
typedef vector<vld2> vld3;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef vector<vll2> vll3;
typedef pair<ll, ll> pll;
typedef vector<pll> vpll;
typedef vector<vpll> vpll2;
typedef string str;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define vin(a) {for (auto& _ : (a)) {cin >> _;}}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define forn(i, n) for (int (i) = 0; (i) < int(n); (i)++)
#define all(x) (x).begin(), (x).end()
#define rall(v) adj.rbegin(),adj.rend()
#define sz(a) ((int) ((a).size()))
#define FOR(i,a,b) for (int i=(a); i<=(b); ++i)
#define REP(i,n) for (int i=0; i<(n); ++i)
#define F ffirst
#define S second
#define pb push_back

template<class T> void pv2(vector<vector<T>> a) { cout << "\n"; for (auto& it : a) for (auto& it2 : it) cout << it2 << " "; cout << "\n\n"; }
template<class T> void out(const T& t) { cout << t << "\n"; }
template<class T> void out2(const T& t) { cout << t << " "; }
void first(bool i = true) { out(i ? "first" : "second"); }
void First(bool i = true) { out(i ? "First" : "Second"); }
void yes(bool i = true) { out(i ? "yes" : "no"); }
void Yes(bool i = true) { out(i ? "Yes" : "No"); }
void YES(bool i = true) { out(i ? "YES" : "NO"); }
void No() { out("No"); }
void NO() { out("NO"); }
void Yay(bool i = true) { out(i ? "Yay!" : ":("); }
void possible(bool i = true) { out(i ? "possible" : "impossible"); }
void Possible(bool i = true) { out(i ? "Possible" : "Impossible"); }
void POSSIBLE(bool i = true) { out(i ? "POSSIBLE" : "IMPOSSIBLE"); }
void Case(ll i) { printf("Case #%lld: ", i); }

const int inf = 1e9, mod = 1e9 + 7, N = 1e5 + 5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator () (std::pair<T1, T2> const& pair) const
	{
		std::size_t h1 = std::hash<T1>()(pair.first);
		std::size_t h2 = std::hash<T2>()(pair.second);

		return h1 ^ h2;
	}
};

#define NEUTRAL = 0

struct Node {
	Node* left = NULL;
	Node* right = NULL;
	ll value = 0;
	Node() = default;
	Node(ll v) : value(v) {}
};

class SegmentTree {
private:
	ll size;
	Node* root;

	ll merge(ll x, ll y) {
		return x + y;
	}


	void build(Node* v, ll vl, ll vr, vll& a) {
		//if (v == NULL) v = new Node();
		if (vl == vr) {
			v->value = a[vl];
			return;
		}
		ll vm = vl + (vr - vl) / 2;
		if (v->left == NULL) v->left = new Node();
		if (v->right == NULL) v->right = new Node();
		build(v->left, vl, vm, a);
		build(v->right, vm + 1, vr, a);
		v->value = merge(v->left->value, v->right->value);
	}

	ll query(Node* v, ll vl, ll vr, ll l, ll r) {
		if (vr < l || r < vl)
			return 0;
		if (l <= vl && vr <= r)
			return v->value;
		ll vm = vl + (vr - vl) / 2;
		ll ql = query(v->left, vl, vm, l, r);
		ll qr = query(v->right, vm + 1, vr, l, r);
		return merge(ql, qr);
	}

	void modify(Node* v, ll vl, ll vr, ll index, ll value) {
		if (vr < index || index < vl)
			return;
		if (vl == vr) {
			v->value = value;
			return;
		}
		ll vm = vl + (vr - vl) / 2;
		modify(v->left, vl, vm, index, value);
		modify(v->right, vm + 1, vr, index, value);
		v->value = merge(v->left->value, v->right->value);
	}



public:
	SegmentTree(vll& a) : size(a.size()) {
		root = new Node();
		build(root, 0, size - 1, a);
	}
	ll getSum(ll l, ll r) {
		return query(root, 0, size - 1, l, r);
	}
	void addValue(ll index, ll value) {
		modify(root, 0, size - 1, index, value);
	}

};


ll solve() {
	ll n, m;
	cin >> n >> m;
	vll a(n);
	SegmentTree t(a);
	forn(i, m) {
		char x;
		ll l, r;
		cin >> x >> l >> r;
		l--; r--;
		if (x == 'A') {
			r++;
			t.addValue(l, r);
		}
		else {
			cout << t.getSum(l, r) << "\n";
		}
	}
	return 0;
}



int main() {
	IOS;
	//freopen("a.in", "r", stdin);
	//freopen("a.out", "w", stdout);
	ll tc = 1;
	//cin >> tc;
	while (tc--) {
		solve();
	}
	return 0;
}
