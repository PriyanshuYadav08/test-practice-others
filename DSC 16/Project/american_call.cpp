#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>

using namespace std;

// Call payoff
double payoff_call(double S, double K)
{
    return max(S - K, 0.0);
}

int main()
{
    // Model parameters
    double K = 150.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;
    double q = 0.03;   // ✅ dividend yield (IMPORTANT)

    // Grid parameters
    int M = 200;
    int N = 200;

    double Smax = 350.0;

    double dS = Smax / M;
    double dt = T / N;

    // PSOR parameters
    double omega = 1.2;
    double tol = 1e-6;
    int maxIter = 10000;

    vector<double> S(M+1), V(M+1), V_old(M+1);

    // Asset grid
    for(int i = 0; i <= M; i++)
        S[i] = i * dS;

    // Terminal payoff
    for(int i = 0; i <= M; i++)
        V[i] = payoff_call(S[i], K);

    // Backward time stepping
    for(int n = N; n > 0; n--)
    {
        V_old = V;

        // Boundary conditions
        V[0] = 0.0;
        V[M] = Smax - K;

        for(int iter = 0; iter < maxIter; iter++)
        {
            vector<double> V_prev = V;

            for(int i = 1; i < M; i++)
            {
                double Si = S[i];
                double alpha = 0.5 * sigma * sigma * Si * Si;

                // ✅ drift term uses (r - q)
                double a = -dt * (alpha/(dS*dS) - (r - q)*Si/(2*dS));
                double b = 1 + dt * (2*alpha/(dS*dS) + r);
                double c = -dt * (alpha/(dS*dS) + (r - q)*Si/(2*dS));

                double rhs = V_old[i];

                double continuation =
                    (rhs - a*V[i-1] - c*V[i+1]) / b;

                double value =
                    (1 - omega)*V[i] + omega*continuation;

                // ✅ American constraint
                V[i] = max(payoff_call(Si, K), value);
            }

            // Convergence
            double err = 0.0;
            for(int i = 0; i <= M; i++)
                err = max(err, fabs(V[i] - V_prev[i]));

            if(err < tol)
                break;
        }
    }

    // ✅ Write CSV
    ofstream file("american_call.csv");

    if(file.is_open())
    {
        file << "S,OptionValue\n";

        for(int i = 0; i <= M; i++)
        {
            file << S[i] << "," << V[i] << "\n";
        }

        file.close();
        cout << "american_call.csv created successfully.\n";
    }
    else
    {
        cout << "Error writing file.\n";
    }

    return 0;
}