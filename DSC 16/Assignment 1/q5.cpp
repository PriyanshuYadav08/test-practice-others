#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
static double poly(double x) { return x * x * x * x - 18.0 * x * x + 45.0; }

void run_methods(double a, double b, int n, double exact)
{
    double l = a, h = b, p;
    for (int i = 0; i < n; i++)
    {
        p = l + (h - l) / 2.0;
        if ((pow(l, 4) - 18 * l * l + 45) * (pow(p, 4) - 18 * p * p + 45) < 0)
            h = p;
        else
            l = p;
    }
    cout << " Bisection Err : " << abs(p - exact) << endl;
}

int main()
{
    cout << fixed << setprecision(8);
    run_methods(1.0, 2.0, 50, sqrt(3.0));
    return 0;
}