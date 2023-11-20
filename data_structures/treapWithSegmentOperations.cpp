#include <bits/stdc++.h>
using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
typedef long long ll;


int calcGcd(int a, int b) {
    return b ? calcGcd(b, a % b) : a;
}


class Treap {
    static minstd_rand generator;

    struct Node {
        int key, priority;
        int size;
        ll sum;
        int gcd;
        Node* l = nullptr, * r = nullptr;
        Node(int key) : key(key), priority(generator()), size(1), sum(key), gcd(key) {}
    } *root = nullptr;
    static int getSize(Node* n) {
        return n ? n->size : 0;
    }
    static ll getSum(Node* n) {
        return n ? n->sum : 0;
    }
    static int getGcd(Node* n) {
        return n ? n->gcd : 0;
    }
    static void update(Node*& n) {
        if (n) {
            n->size = getSize(n->l) + 1 + getSize(n->r);
            n->sum = getSum(n->l) + n->key + getSum(n->r);
            n->gcd = calcGcd(calcGcd(getGcd(n->l), n->key), getGcd(n->r));
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
        //если надо удалить один ключ, а не все ключи равные key
        // if (equal) equal = merge(equal->l, equal->r);
        // root = merge(merge(less, equal), greater);

        // иначе это
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

    ll sum(int l, int r) {
        Node* less, *equal, *greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        // в less попадут все, которые меньше l
        // в greater попадут все, которые больше r
        // в equal сумма нужных
        ll res = getSum(equal);
        root = merge(merge(less, equal), greater);
        return res;
    }

    int gcd() {
        return getGcd(root);
    }
    int gcd(int l, int r) {
        Node *less, *equal, *greater;
        split(root, l, less, greater);
        split(greater, r + 1, equal, greater);
        int res = getGcd(equal);
        root = merge(merge(less, equal), greater);
        return res;
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
    
    {
        // Test 1: indexByKey
        cout << t.indexByKey(14) << "\n";
        cout << t.indexByKey(23) << "\n";
        cout << t.indexByKey(46) << "\n";
        cout << t.indexByKey(55) << "\n";
        cout << t.indexByKey(67) << "\n";
        cout << "\n\n\n";
        assert(t.indexByKey(14) == 0);
        assert(t.indexByKey(23) == 1);
        assert(t.indexByKey(46) == 2);
        assert(t.indexByKey(55) == 3);
        assert(t.indexByKey(67) == 4);
    }
    {
        // Test 2: keyByIndex
        cout << t.keyByIndex(0) << "\n";
        cout << t.keyByIndex(1) << "\n";
        cout << t.keyByIndex(2) << "\n";
        cout << t.keyByIndex(3) << "\n";
        cout << t.keyByIndex(4) << "\n";
        cout << "\n\n\n";
        assert(t.keyByIndex(0) == 14);
        assert(t.keyByIndex(1) == 23);
        assert(t.keyByIndex(2) == 46);
        assert(t.keyByIndex(3) == 55);
        assert(t.keyByIndex(4) == 67);
    }
    {
        // Test 3: segment sum
        t.insert(5);
        t.insert(9);
        t.insert(7);
        t.insert(2);
        cout << t.sum(5, 10) << "\n";
        assert(t.sum(5, 10) == 21);
        t.erase(7);
        cout << t.sum(5, 10) << "\n";
        assert(t.sum(5, 10) == 14);
        t.insert(12);
        cout << t.sum(5, 15) << "\n";
        cout << "\n\n\n";
        assert(t.sum(5, 15) == 40);
    }
    {
        // Test 4: segment gcd
        cout << t.gcd() << "\n";
        assert(t.gcd() == 1);
        t.insert(4);
        cout << t.gcd(2, 4) << "\n";
        assert(t.gcd(2, 4) == 2);
        t.insert(6);
        t.insert(9);
        cout << t.gcd(6, 9) << "\n";
        assert(t.gcd(6, 9) == 3);
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
