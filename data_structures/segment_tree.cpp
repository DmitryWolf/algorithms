#include <bits/stdc++.h>

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)

using namespace std;

typedef long long ll;

struct SegmentTree {
private:
    int size;
    vector<long long> t;

    void build(int v, int vl, int vr, vector<int>& a) {
        if (vl == vr) {
            t[v] = a[vl];
            return;
        }
        int vm = vl + (vr - vl) / 2;
        build(2 * v + 1, vl, vm, a);
        build(2 * v + 2, vm + 1, vr, a);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }

    long long query(int v, int vl, int vr, int l, int r) {
        if (vr < l || r < vl)
            return 0;
        if (l <= vl && vr <= r)
            return t[v];
        int vm = vl + (vr - vl) / 2;
        long long ql = query(2 * v + 1, vl, vm, l, r);
        long long qr = query(2 * v + 2, vm + 1, vr, l, r);
        return ql + qr;
    }

    void modify(int v, int vl, int vr, int index, int value) {
        if (vr < index || index < vl)
            return;
        if (vl == vr) {
            t[v] += value;
            return;
        }
        int vm = vl + (vr - vl) / 2;
        modify(2 * v + 1, vl, vm, index, value);
        modify(2 * v + 2, vm + 1, vr, index, value);
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }
public:
    SegmentTree(vector<int>& a) :
        size(a.size()), t(4 * a.size()) {
        build(0, 0, size - 1, a);
    }

    long long getSum(int l, int r) {
        return query(0, 0, size - 1, l, r);
    }

    void addValue(int index, int value) {
        modify(0, 0, size - 1, index, value);
    }
};

ll solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SegmentTree tree(a);
    
    // first test
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int temp1 = tree.getSum(i, j), temp2 = 0;
            for (int k = i; k <= j; k++) {
                temp2 += a[k];
            }
            assert(temp1 == temp2);
        }
    }

    // second test
    for (int i = 0; i < n; i++) {
        tree.addValue(i, i);
        a[i] += i;
        assert(a[i] == tree.getSum(i, i));
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
