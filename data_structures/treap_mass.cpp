#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;

class Treap {
    static minstd_rand generator;

    struct Node {
        int key, priority;
        int value, maxValue, addValue = 0;
        Node* l = nullptr, * r = nullptr;
        Node(int key, int value) : key(key), priority(generator()), value(value), maxValue(value) {}
    } *root = nullptr;
    static int getMaxValue(Node* n) {
        return n ? n->maxValue + n->addValue : -1e9;
    }

    static void update(Node*& n) {
        if (n) {
            n->maxValue = max(max(getMaxValue(n->l), n->value), getMaxValue(n->r));
        }
    }

    static void push(Node* n) {
        if (n && n->addValue) {
            n->value += n->addValue;
            n->maxValue += n->addValue;
            if (n->l) n->l->addValue += n->addValue;
            if (n->r) n->r->addValue += n->addValue;
            n->addValue = 0;
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

    int rangeMax(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        // equal contains [l,r]
        int res = getMaxValue(equal);
        root = merge(merge(less, equal), greater);
        return res;
    }

    void rangeAdd(int l, int r, int value) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        if (equal) {
            equal->addValue += value;
        }
        root = merge(merge(less, equal), greater);
    }
};

minstd_rand Treap::generator;








ll solve() {
    Treap t;

    {
        // Test 1: rangeMax
        t.insert(5, 13);
        t.insert(8, 10);
        t.insert(10, 22);
        t.insert(15, 8);
        t.insert(17, 14);

        cout << t.rangeMax(0, 100) << "\n";
        assert(t.rangeMax(0, 100) == 22);
        cout << t.rangeMax(0, 9) << "\n";
        assert(t.rangeMax(0, 9) == 13);
        cout << t.rangeMax(11, 20) << "\n";
        assert(t.rangeMax(11, 20) == 14);
        cout << t.rangeMax(15, 15) << "\n";
        assert(t.rangeMax(15, 15) == 8);
        cout << t.rangeMax(11, 14) << "\n";
        assert(t.rangeMax(11, 14) == -1e9);
        cout << "\n\n\n";
    }
    {
        // Test 2: rangeAdd
        t.rangeAdd(15, 20, 100);

        cout << t.rangeMax(0, 100) << "\n";
        assert(t.rangeMax(0, 100) == 114);
        cout << t.rangeMax(0, 10) << "\n";
        assert(t.rangeMax(0, 10) == 22);
        cout << t.rangeMax(11, 15) << "\n";
        assert(t.rangeMax(11, 15) == 108);
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
