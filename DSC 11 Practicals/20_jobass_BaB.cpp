// Job Assignment Problem using Branch and Bound
#include <bits/stdc++.h>
using namespace std;

// Function to calculate the minimum cost for a given cost matrix
int calculateCost(vector<vector<int>> &costMatrix, vector<bool> &assigned, int person, int job) {
    int cost = 0;
    for (int i = 0; i < costMatrix.size(); i++) {
        if (!assigned[i]) {
            cost += costMatrix[person][i];
        }
    }
    return cost;
}

// Structure to represent a node in the Branch and Bound tree
struct Node {
    vector<bool> assigned;
    int cost;
    int person;
    int job;
    int level;

    Node(int n) : assigned(n, false), cost(0), person(-1), job(-1), level(0) {}
};

// Comparison function for priority queue
struct Compare {
    bool operator()(Node *a, Node *b) {
        return a->cost > b->cost;
    }
};

// Function to solve the Job Assignment Problem
int jobAssignment(vector<vector<int>> &costMatrix) {
    int n = costMatrix.size();
    priority_queue<Node *, vector<Node *>, Compare> pq;

    Node *root = new Node(n);
    pq.push(root);

    int minCost = INT_MAX;

    while (!pq.empty()) {
        Node *current = pq.top();
        pq.pop();

        if (current->level == n) {
            minCost = min(minCost, current->cost);
            continue;
        }

        for (int j = 0; j < n; j++) {
            if (!current->assigned[j]) {
                Node *child = new Node(n);
                child->assigned = current->assigned;
                child->assigned[j] = true;
                child->cost = current->cost + costMatrix[current->level][j];
                child->level = current->level + 1;

                pq.push(child);
            }
        }
    }

    return minCost;
}

int main() {
    vector<vector<int>> costMatrix = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };

    cout << "Minimum cost = " << jobAssignment(costMatrix) << endl;

    return 0;
}