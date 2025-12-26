#ifndef MATRIX_H
#define MATRIX_H

#include <string>

class Matrix {
public:
	Matrix();
	Matrix(const int *data, int rows, int cols);
	Matrix(const Matrix &other);
	Matrix &operator=(Matrix other);
	~Matrix();

	int getRows() const { return rows_; }
	int getCols() const { return cols_; }

	int getElement(int r, int c) const;
	std::string getString() const;

	// Operators
	Matrix operator+(const Matrix &other) const;
	Matrix operator-(const Matrix &other) const;
	Matrix operator*(const Matrix &other) const; // matrix multiplication
	Matrix operator*(int scalar) const; // matrix * scalar

	friend Matrix operator*(int scalar, const Matrix &matrix); // scalar * matrix

private:
	int rows_ = 0;
	int cols_ = 0;
	int *data_ = nullptr;

	// Helper: return a new matrix scaled by scalar
	Matrix scalarMultiplication(int scalar) const;

	void swap(Matrix &other) noexcept;
};

#endif // MATRIX_H

