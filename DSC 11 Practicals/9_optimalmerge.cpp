#include <bits/stdc++.h>
using namespace std;

int optimalMerge(vector<int> files) {
    priority_queue<int, vector<int>, greater<int>> minHeap(files.begin(), files.end());
    int totalCost = 0;

    while (minHeap.size() > 1) {
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        int mergedFile = first + second;
        totalCost += mergedFile;
        minHeap.push(mergedFile);
    }

    return totalCost;
}

int main() {
    vector<int> files = {5, 2, 4, 7};
    cout << "Minimum cost to merge files = " << optimalMerge(files) << endl;
    return 0;
}