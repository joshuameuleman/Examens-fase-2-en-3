#include "matrix.h"

#include <sstream>
#include <cassert>
#include <algorithm>

Matrix::Matrix() = default;

Matrix::Matrix(const int *data, int rows, int cols)
	: rows_(rows), cols_(cols)
{
	assert(rows >= 0 && cols >= 0);
	if (rows_ > 0 && cols_ > 0) {
		data_ = new int[rows_ * cols_];
		if (data) {
			for (int r = 0; r < rows_; ++r)
				for (int c = 0; c < cols_; ++c)
					data_[r * cols_ + c] = data[r * cols + c];
		} else {
			for (int i = 0; i < rows_ * cols_; ++i) data_[i] = 0;
		}
	}
}

Matrix::Matrix(const Matrix &other)
	: rows_(other.rows_), cols_(other.cols_)
{
	if (rows_ > 0 && cols_ > 0) {
		data_ = new int[rows_ * cols_];
		std::copy(other.data_, other.data_ + rows_ * cols_, data_);
	}
}

Matrix &Matrix::operator=(Matrix other)
{
	swap(other);
	return *this;
}

Matrix::~Matrix()
{
	delete[] data_;
}

int Matrix::getElement(int r, int c) const
{
	assert(r >= 0 && r < rows_ && c >= 0 && c < cols_);
	return data_[r * cols_ + c];
}

std::string Matrix::getString() const
{
	std::ostringstream oss;
	for (int r = 0; r < rows_; ++r) {
		for (int c = 0; c < cols_; ++c) {
			if (c) oss << ' ';
			oss << getElement(r, c);
		}
		if (r != rows_ - 1) oss << '\n';
	}
	return oss.str();
}

Matrix Matrix::operator+(const Matrix &other) const
{
	assert(rows_ == other.rows_ && cols_ == other.cols_);
	Matrix result(nullptr, rows_, cols_);
	if (rows_ == 0 || cols_ == 0) return result;
	for (int r = 0; r < rows_; ++r)
		for (int c = 0; c < cols_; ++c)
			result.data_[r * cols_ + c] = getElement(r, c) + other.getElement(r, c);
	return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
	assert(rows_ == other.rows_ && cols_ == other.cols_);
	Matrix result(nullptr, rows_, cols_);
	if (rows_ == 0 || cols_ == 0) return result;
	for (int r = 0; r < rows_; ++r)
		for (int c = 0; c < cols_; ++c)
			result.data_[r * cols_ + c] = getElement(r, c) - other.getElement(r, c);
	return result;
}

Matrix Matrix::scalarMultiplication(int scalar) const
{
	Matrix result(nullptr, rows_, cols_);
	if (rows_ == 0 || cols_ == 0) return result;
	for (int i = 0; i < rows_ * cols_; ++i)
		result.data_[i] = data_[i] * scalar;
	return result;
}

Matrix Matrix::operator*(int scalar) const
{
	return scalarMultiplication(scalar);
}

Matrix operator*(int scalar, const Matrix &matrix)
{
	return matrix.scalarMultiplication(scalar);
}

Matrix Matrix::operator*(const Matrix &other) const
{
	assert(cols_ == other.rows_);
	Matrix result(nullptr, rows_, other.cols_);
	if (rows_ == 0 || cols_ == 0 || other.cols_ == 0) return result;
	for (int r = 0; r < rows_; ++r) {
		for (int c = 0; c < other.cols_; ++c) {
			int sum = 0;
			for (int k = 0; k < cols_; ++k) {
				sum += getElement(r, k) * other.getElement(k, c);
			}
			result.data_[r * result.cols_ + c] = sum;
		}
	}
	return result;
}

void Matrix::swap(Matrix &other) noexcept
{
	std::swap(rows_, other.rows_);
	std::swap(cols_, other.cols_);
	std::swap(data_, other.data_);
}

