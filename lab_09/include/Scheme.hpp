#pragma once

#include <iostream>

#include "Figure.hpp"

class Scheme {
public:
    Scheme(int capacity); 
    ~Scheme();

    void push_back_figure(Figure* fg);
    void remove_figure(int id); // элементы смещаются влево

    void print_all_figures();
    void zoom_figure(int id, int factor);
    Figure* is_inside_figure(int x, int y); // если внутри нескольких фигур, то возвращается любая из них
    void move(int id, int new_x, int new_y);

private:
    std::size_t get_figure_index(int id); // возращает индекс фигуры с нужным id

private:
    std::size_t sz = 0;
    Figure** figures_; // размер массива задается в конструкторе и больше не растет
};