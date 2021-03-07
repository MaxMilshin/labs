#include "matrix.hpp"

#include <iostream>

Matrix::Matrix(std::size_t r, std::size_t c) {
	_rows = r;
	_cols = c;
	_data = new int*[r];
	int* data = new int[r * c];
	for (size_t i = 0; i < r; i++) {
		_data[i] = &(data[c * i]);
	}
	for (size_t i = 0; i < _rows; i++)
		for (size_t j = 0; j < _cols; j++)
			_data[i][j] = 0;
}

Matrix::Matrix(const Matrix& that) {
	_rows = that._rows;
	_cols = that._cols;
	_data = new int*[_rows];
	int* data = new int[_rows * _cols];
	for (size_t i = 0; i < _rows; i++) {
		_data[i] = &(data[_cols * i]);
	}
	for (size_t i = 0; i < _rows; i++)
		for (size_t j = 0; j < _cols; j++)
			_data[i][j] = that._data[i][j]; 
}

Matrix& Matrix::operator =(Matrix that) {
	std::swap(_data, that._data);
	std::swap(_rows, that._rows);
	std::swap(_cols, that._cols);
	return *this;
}

Matrix::~Matrix() {
	delete [] _data[0];
	delete [] _data;
}

bool Matrix::operator==(const Matrix& that) const {
	if (that._rows != _rows || that._cols != _cols)
		return false;
	for (size_t i = 0; i < _rows; i++) 
		for (size_t j = 0; j < _cols; j++)
			if (_data[i][j] != that._data[i][j])
				return false;		
	return true;
}

bool Matrix::operator!=(const Matrix& that) const {
	return !(*this == that);
}


