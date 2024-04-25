struct node {
    int max = 0;
    int val = 0;
};

struct segtree {
    int size = 1;
    vector<node> tree;

    void init(int n) {
        while (size < n) size *= 2;
        tree.assign(2 * size - 1, node());
    }

    void propagate(int x) {
        if (2 * x + 1 < 2 * size - 1) {
            tree[2 * x + 1].val += tree[x].val;
            tree[2 * x + 1].max += tree[x].val;
        }
        if (2 * x + 2 < 2 * size - 1) {
            tree[2 * x + 2].val += tree[x].val;
            tree[2 * x + 2].max += tree[x].val;
        }
        tree[x].val = 0;
    }

    void update(int x, int lx, int rx, int l, int r, int val) {
        if (lx >= r or rx <= l) return;
        if (lx >= l and rx <= r) {
            tree[x].val += val;
            tree[x].max += val;
            return;
        }
        if (tree[x].val) propagate(x);
        int mx = (lx + rx) / 2;
        update(2 * x + 1, lx, mx, l, r, val);
        update(2 * x + 2, mx, rx, l, r, val);
        tree[x].max = max(tree[2 * x + 1].max, tree[2 * x + 2].max);
    }

    void update(int l, int r, int val) {
        update(0, 0, size, l, r, val);
    }

    int getywithmaxvalue() {
        int max = tree[0].max;
        int x = 0;
        while (2 * x + 1 < 2 * size - 1) {
            if (tree[x].val) propagate(x);
            if (tree[2 * x + 1].max == max) x = 2 * x + 1;
            else x = 2 * x + 2;
        }
        return x - (size - 1);
    }
};
