#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

double infinityNorm(const vector<double>& x_new, const vector<double>&
    x_old) {
    double max_diff = 0.0;

    for (size_t i = 0; i < x_new.size(); ++i) {
        double diff = abs(x_new[i] - x_old[i]);
        if (diff > max_diff) max_diff = diff;
    }
    return max_diff;
}

void solveSystem(const vector<vector<double>>& A, const vector<double>& b,
                 double tol, string method) {
    int n = b.size();
    vector<double> x(n, 0.0);
    vector<double> x_next(n, 0.0);
    int iterations = 0;
    double error = tol + 1.0;

    while (error > tol) {
        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j) {
                    if (method == "Jacobi")
                        sum += A[i][j] * x[j];
                    else if (method == "Gauss-Seidel")
                        sum += A[i][j] * x_next[j];
                }
            }
            x_next[i] = (b[i] - sum) / A[i][i];
        }

        error = infinityNorm(x_next, x);

        if (method == "Jacobi")
            x = x_next;
        else if (method == "Gauss-Seidel") {
            x = x_next;
            for (int i = 0; i < n; i++)
                x_next[i] = x[i]; // Reset for next loop
        }
        iterations++;
    }

    cout << method << " converged in " << iterations << " iterations.\nSolution: ";
    for (double val : x)
        cout << fixed << setprecision(6) << val << " ";
    cout << "\n";
}

int main() {
    double tol = 5e-6;

    vector<vector<double>> A1 = {{4, 1, 1, 1}, {1, 8, 2, 3}, {1, 2, 5, 0},
                                 {-1, 0, 2, 4}};
    vector<double> b1 = {-5, 23, 9, 4};

    vector<vector<double>> A2 = {{4, -1, 0, -2, 0, 0},
                                 {-1, 4, -1, 0, -2, 0},
                                 {0, -1, 4, 0, 0, -1},
                                 {-1, 0, 0, 4, -1, 0},
                                 {0, -1, 0, -1, 4, -1},
                                 {0, 0, -1, 0, -1, 4}};
    vector<double> b2 = {-1, 0, 1, -2, 1, 2};

    cout << "--- System 1(a)---\n";
    solveSystem(A1, b1, tol, "Jacobi");
    solveSystem(A1, b1, tol, "Gauss-Seidel");
    cout << "\n--- System 1(b)---\n";
    solveSystem(A2, b2, tol, "Jacobi");
    solveSystem(A2, b2, tol, "Gauss-Seidel");
    return 0;
}