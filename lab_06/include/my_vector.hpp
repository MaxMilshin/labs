#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <cstddef>

class MyVector {
public: // methods
    MyVector(std::size_t init_capacity = 2);
    MyVector(MyVector const & other);
    ~MyVector();

    void set(std::size_t index, int value) {
        _data[index] = value;
    }
    int get(std::size_t index) const {
        return _data[index];
    }

    std::size_t size() const {
        return _size;
    }
    std::size_t capacity() const {
        return _capacity;
    }

    void reserve(std::size_t new_capacity);
    void resize(std::size_t new_size);

    void push_back(int value);
    void insert(std::size_t index, int value);
    void erase(std::size_t index);

    MyVector & operator =(MyVector other);

private: // fields
    std::size_t _size, _capacity;
    int *_data;
};

#endif