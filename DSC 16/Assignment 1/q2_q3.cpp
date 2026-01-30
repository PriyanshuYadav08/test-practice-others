#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>

using namespace std;

double secant(function<double(double)> f, double p0, double p1)
{
    for (int i = 0; i < 100; ++i)
    {
        double q0 = f(p0), q1 = f(p1);
        if (fabs(q1 - q0) < 1e-12) break;
        double p = p1 - q1 * (p1 - p0) / (q1 - q0);
        if (fabs(p - p1) < 1e-7) return p;
        p0 = p1;
        p1 = p;
    }

    return p1;
}

void question2_3()
{
    double k = secant([](double x) { return 18.0 * exp(-x) - 13.0; }, 0.1, 1.0);
    cout << "k: " << k << endl;

    // Normal Temp
    double t_norm = secant([k](double t) { return 72.0 + 18.0 * exp(-k * t) - 98.6; }, -2.0, 0.0);
    cout << " Time ( Normal ): " << t_norm << " hrs" << endl;

    // Flu Temp
    double t_flu = secant([k](double t) { return 72.0 + t - (1.0 / k) + (18.0 + (1.0 / k)) * exp(-k * t) - 103.0; }, -2.0, 0.0);
    cout << " Time ( Flu ): " << t_flu << " hrs" << endl;
}

int main()
{
    cout << fixed << setprecision(6);
    question2_3();
    return 0;
}