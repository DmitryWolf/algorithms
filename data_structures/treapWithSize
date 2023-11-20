#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;


class Treap {
    static minstd_rand generator;

    struct Node {
        int key, priority;
        int size;
        Node* l = nullptr, * r = nullptr;
        Node(int key) : key(key), priority(generator()), size(1) {}
    } *root = nullptr;
    static int getSize(Node* n) {
        return n ? n->size : 0;
    }

    static void update(Node*& n) {
        if (n) {
            n->size = getSize(n->l) + 1 + getSize(n->r);
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
    static void split(Node* n, int key, Node*& a, Node*& b) {
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

    int next(Node* t) {
        if (!t) return -1e9;
        while (t->l) {
            t = t->l;
        }
        return t->key;
    }

    static int keyByIndex(Node* n, int index) {
        int leftSize = getSize(n->l);
        if (index == leftSize)
            return n->key;
        if (index < leftSize)
            return keyByIndex(n->l, index);
        else {
            return keyByIndex(n->r, index - leftSize - 1);
        }
    }

public:
    bool containsDfs(int key) {
        Node* temp = root;
        while (true) {
            if (temp->key == key) {
                return true;
            }
            else if (temp->key < key) {
                if (temp->l) temp = temp->l;
                else return false;
            }
            else if (temp->key > key) {
                if (temp->r) temp = temp->r;
                else return false;
            }
        }
    }
    bool contains(int key) {
        Node* less, *equal, *greater;
        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        bool result = equal;
        root = merge(merge(less, equal), greater);
        return result;
    }
    void insert(int key) {
        Node* less, *greater;
        split(root, key, less, greater);
        root = merge(merge(less, new Node(key)), greater);
    }

    void erase(int key) {
        Node* less, * equal, * greater;
        split(root, key, less, greater);
        split(greater, key + 1, equal, greater);
        //equal = merge(equal->l, equal->r);
        root = merge(less, greater);
    }
    int next(int key) {
        Node* less, *greater;
        split(root, key, less, greater);
        // в greater >= key
        // в less < key
        int res = next(greater);
        root = merge(less, greater);
        return res;
    }

    int indexByKey(int key) {
        Node *less, *greater;
        split(root, key, less, greater);
        int res = getSize(less);
        root = merge(less, greater);
        return res;
    }
    int keyByIndex(int index) {
        return keyByIndex(root, index);
    }
    int size() {
        return getSize(root);
    }
};

minstd_rand Treap::generator;


ll solve() {
    Treap t;
    t.insert(23);
    t.insert(55);
    t.insert(14);
    t.insert(67);
    t.insert(46);
    
    // 14 23 46 55 67

    cout << t.indexByKey(14) << "\n";
    cout << t.indexByKey(23) << "\n";
    cout << t.indexByKey(46) << "\n";
    cout << t.indexByKey(55) << "\n";
    cout << t.indexByKey(67) << "\n";
    cout << "\n\n\n";
    cout << t.keyByIndex(0) << "\n";
    cout << t.keyByIndex(1) << "\n";
    cout << t.keyByIndex(2) << "\n";
    cout << t.keyByIndex(3) << "\n";
    cout << t.keyByIndex(4) << "\n";
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
