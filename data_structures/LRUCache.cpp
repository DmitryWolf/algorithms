#include <bits/stdc++.h>
using namespace std;
 
 
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
typedef map<ll,ll> mll;
typedef unordered_map<ll,ll> umll;
 
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
 
const int inf = 1e9, mod = 1e9 + 7, MAXN = 2e5 + 5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;
const ll MOD = 1e9 + 7;
 
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const {
        uintmax_t hash = std::hash<int>{}(p.first);
        hash <<= sizeof(uintmax_t) * 4;
        hash ^= std::hash<int>{}(p.second);
        return std::hash<uintmax_t>{}(hash);
    }
};

class LRUCache {
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
        size_ = 0;
    }
    
    int get(int key) {
        if (um_.find(key) == um_.end()){
            return -1;
        }
        change(key, (*um_[key]).second);
        return (*um_[key]).second;
    }
    
    void put(int key, int value) {
        if (um_.find(key) == um_.end()){
            if (size_ == capacity_){
                remove();
            }
            list_.push_back({key, value});
            um_[key] = prev(list_.end());
            size_++;
        }
        else{
            change(key, value);
        }
    }
private:
    void change(int key, int value){
        auto it = um_[key];
        pair<int, int> pairs = {key, value};
        list_.erase(it);
        list_.push_back(pairs);
        um_[key] = prev(list_.end());
    }
    void remove(){
        um_.erase(list_.front().first);
        list_.pop_front();
        size_--;
    }
    unordered_map<int, list<pair<int, int>>::iterator> um_;
    int capacity_;
    int size_;
    list<pair<int, int>> list_;
};

ll solve(){
    LRUCache lRUCache(2);
    lRUCache.put(2, 1);
    lRUCache.put(2, 2);
    lRUCache.get(2);
    lRUCache.put(1, 1);
    lRUCache.put(4, 4);
    lRUCache.get(1);
    return 0;
}
int main(){
    IOS;
    ll tc = 1;
    // cin >> tc;
    while(tc--){
        solve();
    }
    // cout.flush();
    return 0;
}
