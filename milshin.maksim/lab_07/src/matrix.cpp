#include "matrix.hpp"

#include <iostream>

void Matrix::commonConstructor(std::size_t r, std::size_t c)  {
	_rows = r;
	_cols = c;
	_data = new int*[r];
	int* data = new int[r * c];
	for (size_t i = 0; i < r; i++) {
		_data[i] = &(data[c * i]);
	}
}

Matrix::Matrix(std::size_t r, std::size_t c) {
	commonConstructor(r, c);
	for (size_t i = 0; i < _rows; i++)
		for (size_t j = 0; j < _cols; j++)
			_data[i][j] = 0;
}

Matrix::Matrix(Matrix const & m) {
	commonConstructor(m._rows, m._cols);
	for (size_t i = 0; i < _rows; i++)
		for (size_t j = 0; j < _cols; j++)
			_data[i][j] = m._data[i][j]; 
}

Matrix& Matrix::operator =(Matrix m) {
	std::swap(_data, m._data);
	std::swap(_rows, m._rows);
	std::swap(_cols, m._cols);
	return *this;
}

Matrix::~Matrix() {
	delete [] _data[0];
	delete [] _data;
}

void Matrix::print(FILE* f) const {
	for (size_t i = 0; i < _rows; i++) {
		for (size_t j = 0; j < _cols; j++) {
			std::cout << _data[i][j];
			if (j != _cols - 1)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
}

bool Matrix::operator==(Matrix& m) const {
	if (m._rows != _rows || m._cols != _cols)
		return false;
	for (size_t i = 0; i < _rows; i++) 
		for (size_t j = 0; j < _cols; j++)
			if (_data[i][j] != m._data[i][j])
				return false;		
	return true;
}

bool Matrix::operator!=(Matrix& m) const {
	return !(*this == m);
}

Matrix Matrix::operator+(Matrix& m) const {
	Matrix sum(*this);
	sum += m;
	return sum;
}

Matrix Matrix::operator-(Matrix& m) const {
	Matrix difference(*this);
	difference -= m;
	return difference;
}

Matrix& Matrix::operator+=(Matrix& m) {
	for (size_t i = 0; i < _rows; i++)
		for (size_t j = 0; j < _cols; j++) 
			_data[i][j] += m._data[i][j];
	return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
	for (size_t i = 0; i < _rows; i++)
		for (size_t j = 0; j < _cols; j++) 
			_data[i][j] -= m._data[i][j];
	return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
	*this = *this * m;
	return *this;
}

Matrix Matrix::operator*(Matrix& m) const {
	Matrix product(_rows, m._cols);
	for (size_t i = 0; i < _rows; i++) 
		for (size_t j = 0; j < m._cols; j++) 
			for (size_t k = 0; k < _cols; k++)
				product._data[i][j] += _data[i][k] * m._data[k][j];
	return product;
}
