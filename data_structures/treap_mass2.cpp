#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;

class Treap {
    static minstd_rand generator;

    struct Node {
        int key, priority;
        ll value, sum, cnt = 1, add = 0;
        Node* l = nullptr, * r = nullptr;
        Node(int key, int value) : key(key), priority(generator()), value(value), sum(value) {}
    } *root = nullptr;
    static ll getSum(Node* n) {
        return n ? n->sum + n->add * n->cnt : 0;
    }
    static int getCnt(Node* n) {
        return n ? n->cnt : 0;
    }
    static void update(Node*& n) {
        if (n) {
            n->sum = getSum(n->l) + n->value + getSum(n->r);
            n->cnt = getCnt(n->l) + 1 + getCnt(n->r);
        }
    }

    static void push(Node* n) {
        if (n && n->add) {
            n->value += n->add;
            n->sum += n->add * n->cnt;
            if (n->l) n->l->add += n->add;
            if (n->r) n->r->add += n->add;
            n->add = 0;
        }
    }

    static Node *merge(Node* a, Node* b) {
        push(a);
        push(b);
        if (!a || !b) {
            return a ? a : b;
        }
        if (a->priority > b->priority) { // левый
            a->r = merge(a->r, b);
            /*
                a       b                   a
                9       6       =>          15
            a->l a->r                   a->l a->r
             5    3                      5    9
            */
            update(a);
            return a;
        }
        else { // правый
            b->l = merge(a, b->l);
            update(b);
            return b;
        }
    }
    // < k  => a
    // >= k  => b
    static void split(Node* n, int key, Node*& a, Node*& b) {
        push(n);
        if (!n) {
            a = b = nullptr;
            return;
        }
        if (n->key < key) {
            /*
                    n
               n->l   n->r=a' b=b'
            */
            split(n->r, key, n->r, b);
            a = n;
        }
        else {
            /*
                           n
               a=a' n->l=b'   n->r
            */
            split(n->l, key, a, n->l);
            b = n;
        }
        update(a);
        update(b);
    }
public:
    bool get(int key) {
        Node* less, *equal, *greater;
        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        bool result = equal;
        root = merge(merge(less, equal), greater);
        return result;
    }
    void insert(int key, int value) {
        Node* less, *greater;
        split(root, key, less, greater);
        root = merge(merge(less, new Node(key, value)), greater);
    }

    void erase(int key) {
        Node* less, * equal, * greater;
        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        //если надо удалить один ключ, а не все ключи равные key
        // if (equal) equal = merge(equal->l, equal->r);
        // root = merge(merge(less, equal), greater);

        // иначе это
        root = merge(less, greater);
    }
    void erase(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        root = merge(less, greater);
    }

    ll rangeMean(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        // equal contains [l,r]
        ll res = 0;
        if (equal)
            res = getSum(equal) / getCnt(equal); 
        root = merge(merge(less, equal), greater);
        return res;
    }

    void rangeAdd(int l, int r, int value) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        if (equal)
            equal->add += value;
        root = merge(merge(less, equal), greater);
    }
};

minstd_rand Treap::generator;

ll solve() {
    // https://codeforces.com/group/zij6WrDiuE/contest/288013/problem/A
    Treap t;
    int q;
    cin >> q;
    while (q--) {
        string type;
        cin >> type;
        if (type == "Add") {
            int x, p;
            cin >> x >> p;
            t.insert(x, p);
        }
        else if (type == "Sell") {
            int l, r;
            cin >> l >> r;
            t.erase(l, r);
        }
        else if (type == "Change") {
            int l, r, p;
            cin >> l >> r >> p;
            t.rangeAdd(l, r, p);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << t.rangeMean(l, r) << "\n";
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
