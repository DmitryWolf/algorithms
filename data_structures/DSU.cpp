#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

class DSU {

    vector<int> id;
    vector<int> size;

public:

    DSU(int n) {
        for (int i = 0; i < n; i++) {
            id.push_back(i);
            size.push_back(1);
        }
    }

    int find(int x) {
        if (id[x] == x)
            return x;
        return id[x] = find(id[x]);
    }

    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry)
            return;
        if (size[rx] < size[ry]) {
            id[rx] = ry;
            size[ry] += size[rx];
        }
        else {
            id[ry] = rx;
            size[ry] += size[rx];
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

class UFDS {
private:
    int n;
    vector<int> p, rank, s;
public:
    UFDS(int size) {
        p.assign(size, 0); for (int i = 0; i < size; i++) p[i] = i;
        rank.assign(size, 0);
        s.assign(size, 1);
        n = size;
    }

    int find_set(int i) { return (p[i] == i ? i : (p[i] = find_set(i))); }
    bool is_same_set(int i, int j) { return find_set(i) == find_set(j); }
    void union_sets(int i, int j) {
        if (!is_same_set(i, j)) {
            int x = find_set(i), y = find_set(j);
            if (rank[x] > rank[y]) swap(x, y);
            if (rank[x] == rank[y]) ++rank[y];
            p[x] = y;
            s[y] += s[x];
            --n;
        }
    }
    int size_of_set(int i) { return s[find_set(i)]; }
    int number_of_sets() { return n; }
};
/*
Большинство задач, связанных с системой непересекающихся множеств, 
относятся к так называемым оффлайн-задачам, когда все запросы и их порядок известны заранее. 
В этом случае допустимо считать и проанализировать все запросы, а также получать ответы на них в порядке, 
отличном от порядка поступления запросов.

Расчёт различных функций (сумма элементов, максимум и т. п.) на множествах. 
Достаточно определить отдельные массивы для значений данных функций аналогично массиву size[], 
должным образом инициализировать их элементы и обновлять их при слиянии множеств;

Задача о разрезании графа (запросы об удалении рёбер и принадлежности вершин одной компоненте связности) в оффлайн. 
Можно считать запросы и выполнять их в обратном порядке (что будет аналогично добавлению рёбер)

Определение минимального остовного дерева в оффлайн алгоритмом Крускала;
Определение ближайшего общего предка в оффлайн алгоритмом Тарьяна.
*/

ll solve() {
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
