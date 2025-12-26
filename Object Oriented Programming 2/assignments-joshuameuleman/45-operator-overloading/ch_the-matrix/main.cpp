#include "Matrix.h"
#include <iostream>
#include <cassert>
using namespace std;

void doTest(const Matrix &matrixResult, const Matrix &matrixExpected);

int main()
{
    // Init matrix1 and 2:
    int m1[][3] = { {3, 8, 5}, {4, 6, 3}, {2, 5, -3} };
    int m2[][3] = { {7, 0, 8}, {4, -9, 6}, {1, 6, 4} };

    Matrix matrix1 = Matrix(&m1[0][0], 3, 3);
    Matrix matrix2 = Matrix(&m2[0][0], 3, 3);

    cout << "matrix1 =" << endl << matrix1.getString() << endl;    
    cout << "matrix2 =" << endl << matrix2.getString() << endl;

    // Calculations:
    Matrix additionResult = matrix1 + matrix2;
    Matrix subtractionResult = matrix2 - matrix1;
    Matrix scalarMultiplicationResult1 = matrix1 * 5;
    Matrix scalarMultiplicationResult2 = -3 * matrix2;
    Matrix multiplicationResult = matrix1 * matrix2;

    cout << "matrix1 + matrix2 =" << endl << additionResult.getString() << endl;
    cout << "matrix2 - matrix1 =" << endl << subtractionResult.getString() << endl;
    cout << "matrix1 * 5 =" << endl << scalarMultiplicationResult1.getString() << endl;
    cout << "-3 * matrix2 =" << endl << scalarMultiplicationResult2.getString() << endl;
    cout << "matrix1 * matrix2 =" << endl << multiplicationResult.getString() << endl;

    // Tests:
    int ae[][3] = { {10, 8, 13}, {8, -3, 9}, {3, 11, 1} };
    int se[][3] = { {4, -8, 3}, {0, -15, 3}, {-1, 1, 7} };
    int sme1[][3] = { {15, 40, 25}, {20, 30, 15}, {10, 25, -15} };
    int sme2[][3] = { {-21, 0, -24}, {-12, 27, -18}, {-3, -18, -12} };
    int me[][3] = { {58, -42, 92}, {55, -36, 80}, {31, -63, 34} };

    Matrix additionExpected = Matrix(&ae[0][0], 3, 3);
    Matrix subtractionExpected = Matrix(&se[0][0], 3, 3);
    Matrix scalarMultiplicationExpected1 = Matrix(&sme1[0][0], 3, 3);
    Matrix scalarMultiplicationExpected2 = Matrix(&sme2[0][0], 3, 3);
    Matrix multiplicationExpected = Matrix(&me[0][0], 3, 3);

    doTest(additionResult, additionExpected);
    doTest(subtractionResult, subtractionExpected);
    doTest(scalarMultiplicationResult1, scalarMultiplicationExpected1);
    doTest(scalarMultiplicationResult2, scalarMultiplicationExpected2);
    doTest(multiplicationResult, multiplicationExpected);

    return 0;
}

void doTest(const Matrix &matrixResult, const Matrix &matrixExpected)
{
    assert(matrixResult.getString() == matrixExpected.getString());
}