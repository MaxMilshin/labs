#include "my_vector.hpp"

#include <iostream>

MyVector::MyVector(size_t init_capacity) {
    _data = new int[init_capacity];
    _capacity = init_capacity;
    _size = 0;
}

MyVector::MyVector(MyVector const & other) {
    _data = new int[other._capacity];
    _capacity = other._capacity;
    _size = other._size;
    for (int i = 0; i < _size; i++)
        _data[i] = other._data[i];        
}

MyVector::~MyVector() {
    delete [] _data;
}

void MyVector::reserve(size_t new_capacity) {
    if (new_capacity > _capacity) {
        int* new_data = new int[new_capacity];
        for (int i = 0; i < _capacity; i++) {
            new_data[i] = _data[i];
        }
        delete [] _data;
        _data = new_data;
        _capacity = new_capacity;
    } 
}

void MyVector::resize(size_t new_size) {
    reserve(2 * new_size);
    for (int i = _size; i < new_size; i++)
        _data[i] = 0;
    _size = new_size; 
}

void MyVector::push_back(int value) {
    if (_capacity == _size) {
        _capacity == 0 ? reserve(1) : reserve(2 * _capacity);
    }
    _data[_size++] = value;
}

void MyVector::insert(size_t index, int value) {
    if (_capacity == _size) {
        _capacity == 0 ? reserve(1) : reserve(2 * _capacity);
    }
    for (int i = _size - 1; i >= (int) index; i--) {
        _data[i + 1] = _data[i];
    }
    _data[index] = value;
    _size++;
}

void MyVector::erase(size_t index) {
    for (int i = index + 1; i < _size; i++) 
        _data[i - 1] = _data[i];
    _size--;
}

MyVector & MyVector::operator =(MyVector other) {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    return *this;
}