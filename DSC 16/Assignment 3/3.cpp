#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n = 4;
    vector<double> a = {0, 2, -2, -2}; // Lower diagonal
    vector<double> b = {4, 4, 4, 4};   // Main diagonal
    vector<double> c = {-1, -1, -1, 0}; // Upper diagonal
    vector<double> d = {6, -6, 3, 4};   // RHS values

    vector<double> x(n, 0.0);

    // Forward sweep phase
    c[0] = c[0] / b[0];
    d[0] = d[0] / b[0];
    for (int i = 1; i < n; i++) {
        double denom = b[i] - a[i] * c[i - 1];
        c[i] = c[i] / denom;
        d[i] = (d[i] - a[i] * d[i - 1]) / denom;
    }

    // Backward substitution phase
    x[n - 1] = d[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        x[i] = d[i] - c[i] * x[i + 1];
    }

    cout << "Solution to the Tridiagonal System:\n";
    for (int i = 0; i < n; i++) {
        cout << "x_" << i + 1 << " = " << fixed << setprecision(5) << x[i]
             << "\n";
    }

    return 0;
}