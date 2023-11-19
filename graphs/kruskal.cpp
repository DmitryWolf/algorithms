#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;


// Система непересекающихся множеств для быстрого определения, лежат ли концы ребра в разных компонентах связности
struct DSU {
    vector<int> parent;
    
    DSU(int n) {
        for (int v = 0; v < n; v++)
            parent.push_back(v);
    }
    
    int findRoot(int v) {
        return parent[v] == v ? v : parent[v] = findRoot(parent[v]);
    }
    
    bool connected(int v1, int v2) {
        return findRoot(v1) == findRoot(v2);
    }
    
    void merge(int v1, int v2) {
        int r1 = findRoot(v1), r2 = findRoot(v2);
        if (r1 == r2)
            return;
        if (rand() % 2)
            parent[r1] = r2;
        else
            parent[r2] = r1;
    }
};

// Структура для хранения взвешенного ребра
// Рёбра сравниваются по весу, список рёбер будет сортироваться по неубыванию весов

struct Edge {
    int a, b, weight;
    
    bool operator < (const Edge &that) const {
        return weight < that.weight;
    }
};



ll solve() {
    // Считывание списка рёбер графа
    // (вершины во вводе нумеруются с 1, во внутреннем представлении — с 0)
    int vertexCount, edgeCount;
    cin >> vertexCount >> edgeCount;

    vector<Edge> edges(edgeCount);
    for (auto &[a, b, weight] : edges) {
        cin >> a >> b >> weight;
        a--;
        b--;
    }

    // Алгоритм Краскала
    // (в данном примере определяется вес минимального остовного дерева — mstWeight)
    ll mstWeight = 0;
    sort(edges.begin(), edges.end());

    DSU dsu(vertexCount);
    for (auto &[a, b, weight] : edges) {
        if (!dsu.connected(a, b)) {
            dsu.merge(a, b);
            mstWeight += weight;
        }
    }
    cout << mstWeight << endl;
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
