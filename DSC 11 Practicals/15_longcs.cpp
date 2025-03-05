#include <bits/stdc++.h>
using namespace std;

int lcs(string X, string Y) {
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> L(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    return L[m][n];
}

int main() {
    string X, Y;
    cout << "Enter first string = ";
    cin >> X;
    cout << "Enter second string = ";
    cin >> Y;

    cout << "Length of LCS is " << lcs(X, Y) << endl;

    return 0;
}