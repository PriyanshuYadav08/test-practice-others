/*

ALGO FOR DIJKSTRA
Algorithm -
    Initialize -
        Create a distance array and set all distances to infinity except the source.
        Use a priority queue (min-heap) to always process the nearest node.

    Relaxation -
        Extract the node with the minimum distance.
        Update the distances of its neighbors if a shorter path is found.

    Repeat until all nodes are processed.
    Return the shortest distances from the source.

TIME COMPLEXITY
    Using a priority queue (min-heap) -
        Each node is extracted once - O(VlogV)
        Each edge is relaxed once - O(ElogV)
        Total - O((V+E)logV)

*/

#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX // Define infinity

// Dijkstra's Algorithm function
void dijkstra(int V, vector<pair<int, int>> adj[], int src) {
    vector<int> dist(V, INF); // Distance array, initialized to INF
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src}); // {distance, node}

    while (!pq.empty()) {
        int u = pq.top().second; // Get the node with the smallest distance
        int currDist = pq.top().first;
        pq.pop();

        if (currDist > dist[u]) continue; // Ignore outdated entries

        for (auto it : adj[u]) {
            int v = it.first;    // Adjacent node
            int weight = it.second; // Edge weight

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print the shortest distances
    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "To " << i << " -> " << (dist[i] == INF ? -1 : dist[i]) << endl;
    }
}

int main() {
    int V = 5; // Number of vertices
    vector<pair<int, int>> adj[V]; // Adjacency list

    // Adding edges: (node1, node2, weight)
    adj[0].push_back({1, 2});
    adj[0].push_back({3, 1});
    adj[1].push_back({2, 3});
    adj[1].push_back({3, 2});
    adj[2].push_back({4, 1});
    adj[3].push_back({4, 6});

    int src = 0; // Source node
    dijkstra(V, adj, src); // Run Dijkstra's Algorithm

    return 0;
}