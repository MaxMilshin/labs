#include <fstream>
#include <vector>
#include <memory>

#include "matrix.hpp"

Matrix::Matrix(std::size_t rows, std::size_t cols) : 
	rows(rows), cols(cols), 
	data(std::vector<std::vector<int>>(rows, std::vector<int>(cols))) {}

void Matrix::operator = (Matrix other) {
	std::swap(data, other.data);
	std::swap(rows, other.rows);
	std::swap(cols, other.cols);
}


void Matrix::load(Matrix &destination, std::ifstream &in) {
	std::size_t rows, cols;
	if (!(in >> rows >> cols)) {
		throw MatrixException("LOAD: invalid file format.");
	}
	std::unique_ptr<Matrix> matrix(new Matrix(rows, cols)); 
	// Matrix* matrix = new Matrix(rows, cols);
	in >> *matrix;
	destination = *matrix;
}

std::ifstream& operator >>(std::ifstream &in, Matrix &matrix) {
	for (std::size_t i = 0; i < matrix.rows; i++) {
		for (std::size_t j = 0; j < matrix.cols; j++) {
			if (!(in >> matrix.data[i][j])) {
				throw MatrixException("LOAD: invalid file format.");
			}
		}
	}
	return in;
}


void Matrix::print() const noexcept {
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			std::cout << data[i][j];
			if (j + 1 < cols) {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
}

void Matrix::add(const Matrix & other) {
	*this += other; 
}

void Matrix::operator +=(const Matrix & other) {
	if (rows != other.rows || cols != other.cols) {
		throw MatrixException("ADD: dimensions do not match."); 
	}
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			data[i][j] += other.data[i][j];
		}
	}
}

void Matrix::multiply(const Matrix & other) {
	*this = *(*this * other);
}

std::unique_ptr<Matrix> Matrix::operator *(const Matrix & other) const {
	if (cols != other.rows) {
		throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
	}
	Matrix* product = new Matrix(rows, other.cols);
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < other.cols; j++) {
			for (std::size_t k = 0; k < cols; k++) {
				product->data[i][j] += data[i][k] * other.data[k][j]; 
			}
		}
	}
	return std::unique_ptr<Matrix>(product);
}

int Matrix::get_element(int row, int col) const {
	if (col < 0 || row < 0 || col >= (int)cols || row >= (int)rows) {
		throw MatrixException("ACCESS: bad index.");
	}
	return data[row][col];
}