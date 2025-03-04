#include <bits/stdc++.h>
using namespace std;

// Function to calculate the size of the number
int getSize(long long num) {
    int size = 0;
    while (num != 0) {
        size++;
        num /= 10;
    }
    return size;
}

// Function to multiply two numbers using Karatsuba algorithm
long long karatsuba(long long x, long long y) {
    // Base case for recursion
    if (x < 10 || y < 10) {
        return x * y;
    }

    // Calculate the size of the numbers
    int size = max(getSize(x), getSize(y));
    int halfSize = size / 2;

    // Split the digit sequences in the middle
    long long high1 = x / pow(10, halfSize);
    long long low1 = x % (long long)pow(10, halfSize);
    long long high2 = y / pow(10, halfSize);
    long long low2 = y % (long long)pow(10, halfSize);

    // 3 recursive calls made to numbers approximately half the size
    long long z0 = karatsuba(low1, low2);
    long long z1 = karatsuba((low1 + high1), (low2 + high2));
    long long z2 = karatsuba(high1, high2);

    return (z2 * pow(10, 2 * halfSize)) + ((z1 - z2 - z0) * pow(10, halfSize)) + z0;
}

int main() {
    long long num1, num2;
    cout << "Enter num1 = ";
    cin >> num1;
    cout << "Enter num2 = ";
    cin >> num2;

    cout << "Product of " << num1 << " and " << num2 << " is " << karatsuba(num1, num2) << endl;

    return 0;
}