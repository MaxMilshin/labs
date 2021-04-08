#include <iostream>

class Matrix {
public:
	Matrix(std::size_t rows = 0, std::size_t cols = 0);
	~Matrix() noexcept = default;
	void operator = (Matrix other);

	static void load(Matrix &, std::ifstream &);
	
	void print() const noexcept;

	void add(const Matrix & other);
	void multiply(const Matrix & other);

	int get_element(int row, int col) const;

private:
	friend std::ifstream& operator >>(std::ifstream &, Matrix*);
	void operator +=(const Matrix & other) noexcept;
	Matrix* operator *(const Matrix & other) const noexcept;

private:
	std::size_t rows, cols;
	std::vector<std::vector<int>> data;
};


class MatrixException {
public:
	MatrixException(std::string message) : message(message) {}
	~MatrixException() = default;
	
	std::string get_message() const {
		return message;
	}

private:
	std::string message;
};