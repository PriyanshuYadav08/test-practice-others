#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void question4() {
    auto g1 = [](double x) { return log(4.0 + x - x * x); };
    double p = 1.5;
    for (int i = 0; i < 10; ++i) {
        double arg = 4.0 + p - p * p;
        if (arg <= 0.0) {
            cerr << "Iteration " << i << " : argument to log non-positive (" << arg << "), stopping.\n";
            break;
        }
        p = g1(p);
    }

    cout << fixed << setprecision(6);
    cout << "g1(x) result : " << p << endl;
}

int main()
{
    question4();
    return 0;
}