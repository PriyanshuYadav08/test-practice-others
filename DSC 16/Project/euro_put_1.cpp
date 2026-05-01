#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double payoff_put(double K, double S)
{
    return max(K - S, 0.0);
}

int main()
{
    // Parameters (same as your American case)
    double K = 150.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;

    int M = 200;
    int N = 200;

    double Smax = 350.0;

    double dS = Smax / M;
    double dt = T / N;

    vector<double> S(M+1), V(M+1), V_old(M+1);

    // Grid
    for(int i = 0; i <= M; i++)
        S[i] = i * dS;

    // Terminal payoff
    for(int i = 0; i <= M; i++)
        V[i] = payoff_put(K, S[i]);

    // Backward time stepping
    for(int n = N; n > 0; n--)
    {
        V_old = V;

        // Boundary conditions
        V[0] = K * exp(-r * (T - (n-1)*dt)); // discounted strike
        V[M] = 0.0;

        // Solve tridiagonal system (Gauss-Seidel style)
        for(int iter = 0; iter < 5000; iter++)
        {
            vector<double> V_prev = V;

            for(int i = 1; i < M; i++)
            {
                double Si = S[i];
                double alpha = 0.5 * sigma * sigma * Si * Si;

                double a = -dt * (alpha/(dS*dS) - r*Si/(2*dS));
                double b = 1 + dt * (2*alpha/(dS*dS) + r);
                double c = -dt * (alpha/(dS*dS) + r*Si/(2*dS));

                double rhs = V_old[i];

                // NO early exercise constraint
                V[i] = (rhs - a*V[i-1] - c*V[i+1]) / b;
            }

            // Convergence check
            double err = 0.0;
            for(int i = 0; i <= M; i++)
                err = max(err, fabs(V[i] - V_prev[i]));

            if(err < 1e-6)
                break;
        }
    }

    // Output
    cout << "Asset Price   European Put Value\n";

    for(int i = 0; i <= M; i += 20)
        cout << S[i] << "   " << V[i] << endl;

    return 0;
}