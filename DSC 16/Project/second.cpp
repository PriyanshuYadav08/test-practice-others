#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

double payoff_call(double S, double K)
{
    return max(S - K, 0.0);
}

int main()
{
    // Parameters
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;

    int M = 200;
    int N = 200;

    double Smax = 4*K;

    double dS = Smax / M;
    double dt = T / N;

    double omega = 1.2;
    double tol = 1e-6;
    int maxIter = 10000;

    vector<double> S(M+1), V(M+1), V_old(M+1);

    // Grid
    for(int i=0;i<=M;i++)
        S[i] = i*dS;

    // Terminal payoff (CALL)
    for(int i=0;i<=M;i++)
        V[i] = payoff_call(S[i], K);

    // Backward time loop
    for(int n=N; n>0; n--)
    {
        V_old = V;

        // Boundary conditions
        V[0] = 0;                 // call worthless at S=0
        V[M] = Smax - K;          // deep ITM

        for(int iter=0; iter<maxIter; iter++)
        {
            vector<double> V_prev = V;

            for(int i=1;i<M;i++)
            {
                double Si = S[i];
                double alpha = 0.5*sigma*sigma*Si*Si;

                double a = -dt*(alpha/(dS*dS) - r*Si/(2*dS));
                double b = 1 + dt*(2*alpha/(dS*dS) + r);
                double c = -dt*(alpha/(dS*dS) + r*Si/(2*dS));

                double rhs = V_old[i];

                double continuation =
                    (rhs - a*V[i-1] - c*V[i+1]) / b;

                double value =
                    (1-omega)*V[i] + omega*continuation;

                // Early exercise condition (almost inactive here)
                V[i] = max(payoff_call(Si,K), value);
            }

            double err=0;
            for(int i=0;i<=M;i++)
                err = max(err, fabs(V[i]-V_prev[i]));

            if(err < tol)
                break;
        }
    }

    cout << "Asset Price   Call Value\n";
    for(int i=0;i<=M;i+=20)
        cout << S[i] << "   " << V[i] << endl;

    return 0;
}