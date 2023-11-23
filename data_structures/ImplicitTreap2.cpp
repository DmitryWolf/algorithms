#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;

class Treap {
    static minstd_rand generator;

    struct Node {
        int priority;
        int size;
        int value;
        Node* l = nullptr, *r = nullptr, *p = nullptr;
        Node(int value) : priority(generator()), value(value), size(1) {}
    } *root = nullptr;

    map<int, Node*> location;

    static int getSize(Node* n) {
        return n ? n->size : 0;
    }
    static void update(Node*& n) {
        if (n) {
            n->size = getSize(n->l) + 1 + getSize(n->r);
            setParent(n->l, n);
            setParent(n->r, n);
        }
    }

    static void setParent(Node* n, Node* p) {
        if (n) {
            n->p = p;
        }
    }

    static Node *merge(Node* a, Node* b) {
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

    // разделить n: первые k вершин попадут в a, остальные в b
    static void split(Node* n, int k, Node*& a, Node*& b) {
        if (!n) {
            a = b = nullptr;
            return;
        }
        if (getSize(n->l) < k) {
            /*
                    n
               n->l   n->r=a' b=b'
            */
            split(n->r, k - getSize(n->l) - 1, n->r, b);
            a = n;
        }
        else {
            /*
                           n
               a=a' n->l=b'   n->r
            */
            split(n->l, k, a, n->l);
            b = n;
        }
        update(a);
        update(b);
        setParent(a, nullptr);
        setParent(b, nullptr);
    }

    static int getIndex(Node* n) {
        int index = getSize(n->l);
        while (n->p) {
            if (n->p->r == n)
                index += getSize(n->p->l) + 1;
            n = n->p;
        }
        return index;
    }

public:
    int get(int index) {
        Node* less, * equal, * greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        int result = equal->value;
        root = merge(merge(less, equal), greater);
        return result;
    }
    void pushBack(int value) {
        location[value] = new Node(value);
        root = merge(root, location[value]);
    }
    void pushFront(int value) {
        location[value] = new Node(value);
        root = merge(location[value], root);
    }

    void insert(int index, int value) {
        Node* less, * greater;
        split(root, index, less, greater);
        location[value] = new Node(value);
        root = merge(merge(less, location[value]), greater);
    }

    void erase(int index) {
        Node* less, * equal, * greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        if (equal)
            location.erase(equal->value);
        root = merge(less, greater);
    }

    int size() {
        return getSize(root);
    }

    int getIndex(int value) {
        if (location.count(value)) {
            return getIndex(location[value]);
        }
        else {
            return -1;
        }
    }
    void toFront(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(merge(equal, less), greater);
    }
    void toBack(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(merge(less, greater), equal);
    }
};

minstd_rand Treap::generator;








ll solve() {
    Treap t;

    // codeforces.com/gym/102150/problem/A

    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        t.pushBack(i);
    }
    for (int i = 0; i < q; i++) {
        string type;
        cin >> type;
        if (type == "shuffle") {
            int l, r;
            cin >> l >> r;
            t.toBack(l, r);
        }
        else {
            int value;
            cin >> value;
            cout << t.getIndex(value) << "\n";
        }
    }
    /*
    // Test 1
    {
        t.pushBack(333);
        t.pushBack(111);
        for (int i = 0; i < t.size(); i++) {
            cout << t.get(i) << " ";
        }
        cout << "\n\n";
        assert(t.get(0) == 333);
        assert(t.get(1) == 111);
    }



    // Test 2
    {
        t.pushFront(222);
        for (int i = 0; i < t.size(); i++) {
            cout << t.get(i) << " ";
        }
        cout << "\n\n";
        assert(t.get(0) == 222);
        assert(t.get(1) == 333);
        assert(t.get(2) == 111);
    }


    // Test 3
    {
        t.insert(2, 0);
        for (int i = 0; i < t.size(); i++) {
            cout << t.get(i) << " ";
        }
        cout << "\n\n";
        assert(t.get(0) == 222);
        assert(t.get(1) == 333);
        assert(t.get(2) == 0);
        assert(t.get(3) == 111);
    }

    // Test 4
    {
        t.pushBack(3);
        t.pushBack(14);
        t.pushBack(15);
        t.pushBack(92);
        t.pushBack(6);
        cout << t.getIndex(3) << "\n";
        assert(t.getIndex(3) == 0);
        cout << t.getIndex(15) << "\n";
        assert(t.getIndex(15) == 2);
        cout << t.getIndex(92) << "\n";
        assert(t.getIndex(92) == 3);
        cout << t.getIndex(100) << "\n";
        assert(t.getIndex(123) == -1);
    }
    */
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
