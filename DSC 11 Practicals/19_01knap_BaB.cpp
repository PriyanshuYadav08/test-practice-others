// 0/1 knapsack problem using branch and bound
#include <bits/stdc++.h>
using namespace std;

// Structure for items
struct Item {
    int weight, value;
    double valuePerWeight;
};

// Structure for a node in the decision tree
struct Node {
    int level, profit, weight;
    double bound;
};

// Comparison function for sorting items by value/weight ratio
bool compare(Item a, Item b) {
    return a.valuePerWeight > b.valuePerWeight;
}

// Function to calculate the upper bound on profit
double calculateBound(Node u, int n, int W, vector<Item>& items) {
    if (u.weight >= W) return 0;

    double bound = u.profit;
    int totalWeight = u.weight;
    for (int i = u.level + 1; i < n; i++) {
        if (totalWeight + items[i].weight <= W) {
            totalWeight += items[i].weight;
            bound += items[i].value;
        } else {
            bound += (W - totalWeight) * items[i].valuePerWeight;
            break;
        }
    }
    return bound;
}

// Branch and Bound algorithm for 0/1 Knapsack
int knapsackBranchAndBound(int W, vector<Item>& items) {
    sort(items.begin(), items.end(), compare);

    queue<Node> Q;
    Node u, v;
    u.level = -1, u.profit = 0, u.weight = 0;
    Q.push(u);

    int maxProfit = 0;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();

        if (u.level == -1) v.level = 0;
        else if (u.level == (int)items.size() - 1) continue;
        else v.level = u.level + 1;

        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].value;

        if (v.weight <= W && v.profit > maxProfit) maxProfit = v.profit;

        v.bound = calculateBound(v, items.size(), W, items);
        if (v.bound > maxProfit) Q.push(v);

        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, items.size(), W, items);
        if (v.bound > maxProfit) Q.push(v);
    }
    return maxProfit;
}

int main() {
    int n, W;
    cout << "Enter number of items = ";
    cin >> n;
    cout << "Enter knapsack capacity =";
    cin >> W;

    vector<Item> items(n);
    cout << "Enter weight and value of each item = \n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].value;
        items[i].valuePerWeight = (double)items[i].value / items[i].weight;
    }

    int maxProfit = knapsackBranchAndBound(W, items);
    cout << "Maximum profit = " << maxProfit << endl;

    return 0;
}