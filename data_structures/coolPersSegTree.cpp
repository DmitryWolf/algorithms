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


struct Node;
Node f(Node a, Node b);
struct Node {
	Node* l;
	Node* r;
	ll len = {}, maxOnes = {}, prefOnes = {}, sufOnes = {};

	Node(Node* l, Node* r, ll len, ll maxOnes, ll prefOnes, ll sufOnes)
		: l(l), r(r), len(len), maxOnes(maxOnes), prefOnes(prefOnes), sufOnes(sufOnes)
	{}

	Node& operator=(const Node& other) = default;

	Node(Node* a, Node* b) {
		*this = f(*a, *b);
		l = a;
		r = b;
	}
};
Node neutral = Node(nullptr, nullptr, 0, 0, 0, 0);

Node f(Node a, Node b) {
	ll maxOnes = max({ a.maxOnes, b.maxOnes, a.sufOnes + b.prefOnes });
	ll len = a.len + b.len;
	ll prefOnes = a.prefOnes;
	ll sufOnes = b.sufOnes;

	if (a.maxOnes == a.len) {
		prefOnes = a.len + b.prefOnes;
	}
	if (b.maxOnes == b.len) {
		sufOnes = a.sufOnes + b.len;
	}
	return { nullptr, nullptr, len, maxOnes, prefOnes, sufOnes };
}

Node* build(ll lx = 0, ll rx = N) {
	if (rx - lx == 1) {
		return new Node(nullptr, nullptr, 1, 0, 0, 0);
	}
	ll mid = (lx + rx) / 2;
	return new Node(build(lx, mid), build(mid, rx));
}

Node* update(Node* node, ll pos, ll val, ll lx = 0, ll rx = N) {
	if (rx - lx == 1) {
		return new Node(nullptr, nullptr, 1, val, val, val);
	}
	ll mid = (lx + rx) / 2;
	if (pos < mid) {
		return new Node(update(node->l, pos, val, lx, mid), node->r);
	}
	else {
		return new Node(node->l, update(node->r, pos, val, mid, rx));
	}
}

Node query(Node* node, ll l, ll r, ll lx = 0, ll rx = N) {
	if (lx >= r || l >= rx) {
		return neutral;
	}
	if (l <= lx && rx <= r) {
		return *node;
	}
	ll mid = (lx + rx) / 2;
	return f(query(node->l, l, r, lx, mid), query(node->r, l, r, mid, rx));
}



ll solve() {
	ll n = 1e5, q;
	cin >> n;
	vll h(n);
	vpll a(n);
	vin(h);
	forn(i, n) {
		a[i].first = h[i];
		a[i].second = i;
	}
	sort(all(a));
	h.clear(); h.resize(n);
	Node* root = build(0, n);

	map<ll, Node*> m;
	set<ll> uniq;
	for (ll i = n - 1; i >= 0; i--) {
		Node* tmp = update(root, a[i].second, 1, 0, n);
		m[a[i].first] = tmp;
		uniq.insert(a[i].first);
	}
	vll vec;
	for (auto it : uniq) vec.push_back(it);


	cin >> q;
	// l, r, w
	forn(i, q) {
		ll l, r, w;
		cin >> l >> r >> w;
		l--; r--;
		ll tl = 0, tr = vec.size();
		while (tr - tl > 1) {
			ll mid = tl + (tr - tl) / 2;
			Node tempWidth = query(m[vec[mid]], l, r + 1, 0, n);
			if (tempWidth.maxOnes >= w) tl = mid;
			else tr = mid;
			// maxOnes >= w => OK
		}
		out(vec[tl]);

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
