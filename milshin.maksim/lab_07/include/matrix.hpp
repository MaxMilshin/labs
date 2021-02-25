#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(Matrix const & m);
    Matrix& operator =(Matrix m);
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
    void print(FILE *f) const;

    Matrix operator+(Matrix& m) const;
    Matrix operator-(Matrix& m) const;
    Matrix operator*(Matrix& m) const;

    Matrix& operator+=(Matrix& m);
    Matrix& operator-=(Matrix& m);
    Matrix& operator*=(Matrix& m);

    bool operator==(Matrix& m) const;
    bool operator!=(Matrix& m) const;

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;

    Matrix add(Matrix& m, int sign) const;
    void commonConstructor(std::size_t r, std::size_t c);
};

#endif
