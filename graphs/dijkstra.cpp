#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

struct Edge {
	int to, weight;
};

//const int INF = 1e9;
const int INF = numeric_limits<int>::max();

vector<int> dijkstra(vector<vector<Edge>>& graph, int start) {
    vector<bool> visited(graph.size());
    vector<int> dist(graph.size(), INF);
    dist[start] = 0;

    for (int i = 0; i < graph.size(); i++) {
        int nearestV = -1;
        for (int v = 0; v < graph.size(); v++)
            if (!visited[v] && (nearestV == -1 || dist[v] < dist[nearestV]))
                nearestV = v;

        visited[nearestV] = true;

        for (auto& [to, weight] : graph[nearestV])
            if (dist[to] > dist[nearestV] + weight)
                dist[to] = dist[nearestV] + weight;
    }

    return dist;
}

// разряженные графы
vector<int> dijkstra2(vector<vector<Edge>> &graph, int start) {
    vector<int> dist(graph.size(), INF);
    set<pair<int, int>> unvisited;
    dist[start] = 0;
    unvisited.insert({ dist[start], start });

    while (!unvisited.empty()) {
        int nearestV = unvisited.begin()->second;
        unvisited.erase(unvisited.begin());

        for (auto &[to, weight] : graph[nearestV]) {
            if (dist[to] > dist[nearestV] + weight) {
                unvisited.erase({ dist[to], to });
                dist[to] = dist[nearestV] + weight;
                unvisited.insert({ dist[to], to });
            }
        }
    }

    return dist;
}

/*
Для восстановления пути нужно поддерживать массив предков from: 
ячейка from[v] содержит индекс непосредственного предка вершины v на кратчайшем пути от стартовой вершины до v.
Изначально предок каждой вершины не определён, что помечается значением -1; 
обновление предка происходит вместе с обновлением кратчайшего расстояния при успешной релаксации.
После завершения работы алгоритма можно восстановить кратчайший путь от начальной вершины до некоторой достижимой вершины finish в обратном порядке, 
последовательно перемещаясь по массиву from, пока текущая вершина не станет равной -1. 
В конце нужно развернуть получившуюся последовательность вершин.

vector<int> from(n, -1);

if (dist[to] > dist[nearestV] + weight) {             
    dist[to] = dist[nearestV] + weight;
    from[to] = nearestV;          
}
vector<int> path;

for (int v = finish; v != -1; v = from[v])
    path.push_back(v);

reverse(path.begin(), path.end());

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
