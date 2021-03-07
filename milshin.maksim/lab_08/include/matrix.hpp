#pragma once

#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    ~Matrix();

    std::size_t get_rows() const {
        return _rows;
    }
    std::size_t get_cols() const {
        return _cols;
    }
    void set(std::size_t i, std::size_t j, int val) {
        _data[i][j] = val;
    }
    int get(std::size_t i, std::size_t j) const {
        return _data[i][j];
    }

    bool operator==(const Matrix& that) const;
    bool operator!=(const Matrix& that) const;

private:
    Matrix(const Matrix& that);
    Matrix& operator=(Matrix that);

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};