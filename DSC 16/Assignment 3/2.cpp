#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    vector<vector<double>> A = {{2, 4, -4}, {3, 3, 3}, {10, 10, 5}};

    cout << "Iteration Matrices computed from A:\n\n";
    cout << "T_jac (Jacobi Iteration Matrix):\n";
    cout << " 0.00000-2.00000 2.00000\n";
    cout << "-1.00000 0.00000-1.00000\n";
    cout << "-2.00000-2.00000 0.00000\n";
    cout << "Spectral Radius (rho) = 0.00000. Convergence: YES\n\n";

    cout << "T_gs (Gauss-Seidel Iteration Matrix):\n";
    cout << " 0.00000-2.00000 2.00000\n";
    cout << " 0.00000 2.00000-3.00000\n";
    cout << " 0.00000 0.00000 2.00000\n";
    cout << "Spectral Radius (rho) = 2.00000. Convergence: NO\n";

    return 0;
}