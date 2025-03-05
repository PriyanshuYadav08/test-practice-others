#include <bits/stdc++.h>
using namespace std;

void addMatrix(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtractMatrix(int **A, int **B, int **C, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int **A, int **B, int **C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    int **A11 = new int*[newSize];
    int **A12 = new int*[newSize];
    int **A21 = new int*[newSize];
    int **A22 = new int*[newSize];
    int **B11 = new int*[newSize];
    int **B12 = new int*[newSize];
    int **B21 = new int*[newSize];
    int **B22 = new int*[newSize];
    int **C11 = new int*[newSize];
    int **C12 = new int*[newSize];
    int **C21 = new int*[newSize];
    int **C22 = new int*[newSize];
    int **M1 = new int*[newSize];
    int **M2 = new int*[newSize];
    int **M3 = new int*[newSize];
    int **M4 = new int*[newSize];
    int **M5 = new int*[newSize];
    int **M6 = new int*[newSize];
    int **M7 = new int*[newSize];
    int **tempA = new int*[newSize];
    int **tempB = new int*[newSize];

    for (int i = 0; i < newSize; i++) {
        A11[i] = new int[newSize];
        A12[i] = new int[newSize];
        A21[i] = new int[newSize];
        A22[i] = new int[newSize];
        B11[i] = new int[newSize];
        B12[i] = new int[newSize];
        B21[i] = new int[newSize];
        B22[i] = new int[newSize];
        C11[i] = new int[newSize];
        C12[i] = new int[newSize];
        C21[i] = new int[newSize];
        C22[i] = new int[newSize];
        M1[i] = new int[newSize];
        M2[i] = new int[newSize];
        M3[i] = new int[newSize];
        M4[i] = new int[newSize];
        M5[i] = new int[newSize];
        M6[i] = new int[newSize];
        M7[i] = new int[newSize];
        tempA[i] = new int[newSize];
        tempB[i] = new int[newSize];
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    addMatrix(A11, A22, tempA, newSize);
    addMatrix(B11, B22, tempB, newSize);
    strassen(tempA, tempB, M1, newSize);

    addMatrix(A21, A22, tempA, newSize);
    strassen(tempA, B11, M2, newSize);

    subtractMatrix(B12, B22, tempB, newSize);
    strassen(A11, tempB, M3, newSize);

    subtractMatrix(B21, B11, tempB, newSize);
    strassen(A22, tempB, M4, newSize);

    addMatrix(A11, A12, tempA, newSize);
    strassen(tempA, B22, M5, newSize);

    subtractMatrix(A21, A11, tempA, newSize);
    addMatrix(B11, B12, tempB, newSize);
    strassen(tempA, tempB, M6, newSize);

    subtractMatrix(A12, A22, tempA, newSize);
    addMatrix(B21, B22, tempB, newSize);
    strassen(tempA, tempB, M7, newSize);

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C12[i][j] = M3[i][j] + M5[i][j];
            C21[i][j] = M2[i][j] + M4[i][j];
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    for (int i = 0; i < newSize; i++) {
        delete[] A11[i];
        delete[] A12[i];
        delete[] A21[i];
        delete[] A22[i];
        delete[] B11[i];
        delete[] B12[i];
        delete[] B21[i];
        delete[] B22[i];
        delete[] C11[i];
        delete[] C12[i];
        delete[] C21[i];
        delete[] C22[i];
        delete[] M1[i];
        delete[] M2[i];
        delete[] M3[i];
        delete[] M4[i];
        delete[] M5[i];
        delete[] M6[i];
        delete[] M7[i];
        delete[] tempA[i];
        delete[] tempB[i];
    }

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] C11;
    delete[] C12;
    delete[] C21;
    delete[] C22;
    delete[] M1;
    delete[] M2;
    delete[] M3;
    delete[] M4;
    delete[] M5;
    delete[] M6;
    delete[] M7;
    delete[] tempA;
    delete[] tempB;
}

int main() {
    int size;
    cout << "Enter the size of the matrix (must be a power of 2): ";
    cin >> size;

    int **A = new int*[size];
    int **B = new int*[size];
    int **C = new int*[size];

    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }

    cout << "Enter elements of matrix A:\n";
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            cin >> A[i][j];

    cout << "Enter elements of matrix B:\n";
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            cin >> B[i][j];

    strassen(A, B, C, size);

    cout << "Resultant matrix C:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            cout << C[i][j] << " ";
        cout << endl;
    }

    for (int i = 0; i < size; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}