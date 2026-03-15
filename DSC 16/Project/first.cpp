#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

int main()
{
    // Parameters
    double Smax = 200.0;
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;

    int M = 200;  // stock steps
    int N = 200;  // time steps

    double dS = Smax / M;
    double dt = T / N;

    double omega = 1.2;
    double tol = 1e-6;
    int max_iter = 10000;

    vector<double> S(M+1);
    vector<double> V(M+1);
    vector<double> payoff(M+1);

    vector<double> a(M+1), b(M+1), c(M+1);
    vector<double> rhs(M+1);

    // Stock grid
    for(int i=0;i<=M;i++)
        S[i] = i*dS;

    // Payoff (American Put)
    for(int i=0;i<=M;i++)
    {
        payoff[i] = max(K - S[i],0.0);
        V[i] = payoff[i];
    }

    // Coefficients
    for(int i=1;i<M;i++)
    {
        double alpha = 0.25*dt*(sigma*sigma*i*i - r*i);
        double beta  = -0.5*dt*(sigma*sigma*i*i + r);
        double gamma = 0.25*dt*(sigma*sigma*i*i + r*i);

        a[i] = -alpha;
        b[i] = 1 - beta;
        c[i] = -gamma;
    }

    // Time stepping backward
    for(int n=N-1;n>=0;n--)
    {
        for(int i=1;i<M;i++)
        {
            double alpha = 0.25*dt*(sigma*sigma*i*i - r*i);
            double beta  = -0.5*dt*(sigma*sigma*i*i + r);
            double gamma = 0.25*dt*(sigma*sigma*i*i + r*i);

            rhs[i] = alpha*V[i-1] + (1+beta)*V[i] + gamma*V[i+1];
        }

        vector<double> V_old = V;

        // PSOR iterations
        for(int iter=0; iter<max_iter; iter++)
        {
            double err = 0.0;

            for(int i=1;i<M;i++)
            {
                double y = (rhs[i] - a[i]*V[i-1] - c[i]*V[i+1]) / b[i];

                double Vnew = (1-omega)*V[i] + omega*y;

                // Early exercise constraint
                Vnew = max(Vnew, payoff[i]);

                err = max(err, fabs(Vnew - V[i]));

                V[i] = Vnew;
            }

            if(err < tol)
                break;
        }

        // Boundary conditions
        V[0] = K;
        V[M] = 0;
    }

    // Save results
    ofstream file("option_surface.csv");

    for(int i=0;i<=M;i++)
    {
        file << S[i] << "," << V[i] << endl;
    }

    file.close();

    cout << "Computation complete. Results saved to option_surface.csv\n";

    return 0;
}