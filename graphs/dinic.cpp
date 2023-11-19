#include <bits/stdc++.h>
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
using namespace std;
typedef long long ll;

class Graph {
    struct Edge {
        int a, b, capacity, flow = 0;

        Edge(int a, int b, int capacity) :
            a(a), b(b), capacity(capacity) {}

        int other(int v) const {
            return v == a ? b : a;
        }

        int capacityTo(int v) const {
            return v == b ? capacity - flow : flow;
        }

        void addFlowTo(int v, int deltaFlow) {
            flow += (v == b ? deltaFlow : -deltaFlow);
        }
    };

    vector<Edge> edges;
    vector<vector<int>> graph;
    vector<int> dist, edgeTo, index;

    bool bfs(int start, int finish) {
        dist.assign(graph.size(), 1e9);
        queue<int> q;

        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int e : graph[v]) {
                int to = edges[e].other(v);
                if (edges[e].capacityTo(to) && dist[to] > dist[v] + 1) {
                    dist[to] = dist[v] + 1;
                    q.push(to);
                }
            }
        }

        return dist[finish] != 1e9;
    }

    bool dfs(int v, int finish) {
        if (v == finish)
            return 1;

        for ( ; index[v] < graph[v].size(); index[v]++) {
            int e = graph[v][index[v]], to = edges[e].other(v);
            if (edges[e].capacityTo(to) && dist[to] == dist[v] + 1 && dfs(to, finish)) {
                edgeTo[to] = e;
                return 1;
            }
        }

        return 0;
    }

    int bottleneckCapacity(int start, int finish) {
        int bCapacity = 1e9;
        for (int v = finish; v != start; v = edges[edgeTo[v]].other(v))
            bCapacity = min(bCapacity, edges[edgeTo[v]].capacityTo(v));
        return bCapacity;
    }

    void addFlow(int start, int finish, int deltaFlow) {
        for (int v = finish; v != start; v = edges[edgeTo[v]].other(v))
            edges[edgeTo[v]].addFlowTo(v, deltaFlow);
    }

public:
    Graph(int vertexCount) :
        graph(vertexCount), dist(vertexCount), edgeTo(vertexCount), index(vertexCount) {}

    void addEdge(int from, int to, int capacity) {
        edges.push_back(Edge(from, to, capacity));
        graph[from].push_back(edges.size() - 1);
        graph[to].push_back(edges.size() - 1);
    }

    long long maxFlow(int start, int finish) {
        long long flow = 0;
        while (bfs(start, finish)) {
            index.assign(graph.size(), 0);
            while (dfs(start, finish)) {
                int deltaFlow = bottleneckCapacity(start, finish);
                addFlow(start, finish, deltaFlow);
                flow += deltaFlow;
            }
        }
        return flow;
    }
};

ll solve() {
    // нумерация 1..n
    // 1 - исток, n - сток
    ll n, m;
    cin >> n >> m;
    ll s = 1, t = n;
    Graph g(n + 1);
    for (int i = 0; i < m; i++){
        ll u, v, c;
        cin >> u >> v >> c;
        g.addEdge(u, v, c);
        g.addEdge(v, u, c);
    }
    cout << g.maxFlow(s, t);
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
