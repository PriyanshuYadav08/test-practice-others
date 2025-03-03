// FLOYD WARSHALL ALGORITHM
// Floyd Warshall Algorithm is used to find the shortest path between all pairs of vertices in a weighted graph. 
//The algorithm works for both the directed and undirected graph.
//But, it does not work for the graph which has negative weight cycle.
//The time complexity of the algorithm is O(V^3) where V is the number of vertices in the graph.

#include <bits/stdc++.h>
using namespace std;

#define INF 1e9

void floydWarshall(vector<vector<int>>& dist, int V) {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> dist(V, vector<int>(V));

    cout << "Enter the adjacency matrix (use " << INF << " for infinity):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> dist[i][j];
        }
    }

    floydWarshall(dist, V);

    cout << "The shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}