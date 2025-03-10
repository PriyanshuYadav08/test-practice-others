#include <bits/stdc++.h>
using namespace std;

#define V 8
const int INF = 1000000000; // Use integer INF to avoid implicit type issues

int tsp(vector<vector<int>> &graph, int pos, int visited, vector<vector<int>> &dp) {
    if (visited == (1 << V) - 1)
        return (graph[pos][0] != INF) ? graph[pos][0] : INF; // Ensure a valid return

    if (dp[pos][visited] != -1)
        return dp[pos][visited];

    int ans = INF;
    for (int city = 0; city < V; city++) {
        if ((visited & (1 << city)) == 0 && graph[pos][city] != INF) { // Check for valid edge
            int newAns = graph[pos][city] + tsp(graph, city, visited | (1 << city), dp);
            ans = min(ans, newAns);
        }
    }

    return dp[pos][visited] = ans;
}

int main() {
    vector<vector<int>> graph = {
        {0, 14, 33, 45, 74, 33, 46, 96},
        {45, 0, INF, 46, 96, 104, 34, 45},
        {93, 82, 0, 49, 32, INF, 24, 32},
        {INF, 45, 10, 0, 40, 32, INF, 15},
        {46, 49, INF, 32, 0, 52, 17, 29},
        {78, INF, 45, 15, 49, 0, 7, INF},
        {84, 55, 73, 9, 32, 74, 0, 42},
        {39, 53, 61, 7, 80, 16, INF, 0}
    };

    vector<vector<int>> dp(V, vector<int>(1 << V, -1));
    int result = tsp(graph, 0, 1, dp);
    
    if (result == INF)
        cout << "No possible route to visit all cities and return to the start.\n";
    else
        cout << "The minimum cost of visiting all cities is " << result << endl;

    return 0;
}
