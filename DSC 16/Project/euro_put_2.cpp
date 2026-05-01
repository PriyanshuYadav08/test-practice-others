#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

double payoff_put(double K, double S)
{
    return max(K - S, 0.0);
}

int main()
{
    // Parameters
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
        V[0] = K * exp(-r * (T - (n-1)*dt));  // discounted strike
        V[M] = 0.0;

        // Iterative solver (Gauss-Seidel)
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

                // European: no early exercise
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

    // ✅ Write full results to CSV
    ofstream file("european_put.csv");

    if(file.is_open())
    {
        file << "S,OptionValue\n";

        for(int i = 0; i <= M; i++)
        {
            file << S[i] << "," << V[i] << "\n";
        }

        file.close();
        cout << "CSV file 'european_put.csv' created successfully.\n";
    }
    else
    {
        cout << "Error creating file.\n";
    }

    return 0;
}