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
        int minValue;
        int add = 0;
        bool rev = 0; // 1 - we need to reverse [l, r]
        Node* l = nullptr, * r = nullptr;
        Node(int value) : priority(generator()), value(value), size(1), minValue(value) {}
    } *root = nullptr;

    static int getSize(Node* n) {
        return n ? n->size : 0;
    }

    static int getMinValue(Node* n) {
        return n ? n->minValue + n->add : 2e9;
    }
    static void push(Node* n) {
        if (n) {
            if (n->add) {
                n->value += n->add;
                n->minValue += n->add;
                if (n->l)
                    n->l->add += n->add;
                if (n->r)
                    n->r->add += n->add;
                n->add = 0;
            }
            if (n->rev) {
                swap(n->l, n->r);
                if (n->l)
                    n->l->rev ^= 1;
                if (n->r)
                    n->r->rev ^= 1;
                n->rev = 0;
            }
        }
    }
    static void update(Node*& n) {
        if (n) {
            n->size = getSize(n->l) + 1 + getSize(n->r);
            n->minValue = min(min(getMinValue(n->l), getMinValue(n->r)), n->value);
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

    // разделить n: первые k вершин попадут в a, остальные в b
    static void split(Node* n, int k, Node*& a, Node*& b) {
        push(n);
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
        root = merge(root, new Node(value));
    }
    void pushFront(int value) {
        root = merge(new Node(value), root);
    }

    void insert(int index, int value) {
        Node* less, * greater;
        split(root, index, less, greater);
        root = merge(merge(less, new Node(value)), greater);
    }

    void erase(int index) {
        Node* less, * equal, * greater;
        split(root, index, less, greater);
        split(greater, 1, equal, greater);
        root = merge(less, greater);
    }
    void erase(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(less, greater);
    }
    int size() {
        return getSize(root);
    }


    void toFront(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        root = merge(merge(equal, less), greater);
    }

    int minValue(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        int result = getMinValue(equal);
        root = merge(merge(less, equal), greater);
        return result;
    }

    void add(int l, int r, int val) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        equal->add += val;
        root = merge(merge(less, equal), greater);
    }
    void reverse(int l, int r) {
        Node* less, * equal, * greater;
        split(root, l, less, greater);
        split(greater, r - l + 1, equal, greater);
        equal->rev ^= 1;
        root = merge(merge(less, equal), greater);
    }
};

minstd_rand Treap::generator;








ll solve() {
    Treap t;
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
        t.erase(1, 2);
        for (int i = 0; i < t.size(); i++) {
            cout << t.get(i) << " ";
        }
        cout << "\n\n";
        assert(t.get(0) == 222);
        assert(t.get(1) == 111);
    }
    
    // Test 5: moveToFront
    {
        t.pushFront(6);
        t.toFront(1, 2);
        for (int i = 0; i < t.size(); i++) {
            cout << t.get(i) << " ";
        }
        cout << "\n\n";
        assert(t.get(0) == 222);
        assert(t.get(1) == 111);
        assert(t.get(2) == 6);
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
