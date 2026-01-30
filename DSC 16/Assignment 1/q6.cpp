#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void question6() {
    double a = 3, b = 5, tol = 1e-5;
    int i = 0;
    while ((b - a) / 2 > tol) {
        i++;
        double p = a + (b - a) / 2;
        double fa = 1.5 * a - 6 - 0.5 * sin(2 * a);
        double fp = 1.5 * p - 6 - 0.5 * sin(2 * p);
        if (fa * fp < 0) b = p; else a = p;
    }
    cout << fixed << setprecision(8);
    cout << "Root : " << a + (b - a) / 2 << " ( Iter : " << i << ")" << endl;
}

int main() {
    question6();
    return 0;
}