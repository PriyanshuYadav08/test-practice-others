#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

void dijkstra(vector<vector<pair<int, int>>> &graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INF);
    dist[src] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto &neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; ++i)
        cout << i << " \t\t " << dist[i] << "\n";
}

int main() {
    int V = 9;
    vector<vector<pair<int, int>>> graph(V);

    graph[0].push_back({1, 4});
    graph[0].push_back({7, 8});
    graph[1].push_back({0, 4});
    graph[1].push_back({2, 8});
    graph[1].push_back({7, 11});
    graph[2].push_back({1, 8});
    graph[2].push_back({3, 7});
    graph[2].push_back({5, 4});
    graph[2].push_back({8, 2});
    graph[3].push_back({2, 7});
    graph[3].push_back({4, 9});
    graph[3].push_back({5, 14});
    graph[4].push_back({3, 9});
    graph[4].push_back({5, 10});
    graph[5].push_back({2, 4});
    graph[5].push_back({3, 14});
    graph[5].push_back({4, 10});
    graph[5].push_back({6, 2});
    graph[6].push_back({5, 2});
    graph[6].push_back({7, 1});
    graph[6].push_back({8, 6});
    graph[7].push_back({0, 8});
    graph[7].push_back({1, 11});
    graph[7].push_back({6, 1});
    graph[7].push_back({8, 7});
    graph[8].push_back({2, 2});
    graph[8].push_back({6, 6});
    graph[8].push_back({7, 7});

    dijkstra(graph, 0);

    return 0;
}