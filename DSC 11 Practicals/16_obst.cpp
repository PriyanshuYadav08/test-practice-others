#include <bits/stdc++.h>
using namespace std;

// Function to calculate the optimal cost of a binary search tree
int optimalBST(vector<int>& keys, vector<int>& freq, int n) {
    vector<vector<int>> cost(n, vector<int>(n, 0));

    // Cost for a single key
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
    }

    // L is the chain length
    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;

            // Try making all keys in interval keys[i..j] as root
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) + 
                        ((r < j) ? cost[r + 1][j] : 0) + 
                        accumulate(freq.begin() + i, freq.begin() + j + 1, 0);

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                }
            }
        }
    }

    return cost[0][n - 1];
}

int main() {
    vector<int> keys = {10, 12, 20};
    vector<int> freq = {34, 8, 50};
    int n = keys.size();

    cout << "Cost of Optimal BST is " << optimalBST(keys, freq, n) << endl;

    return 0;
}