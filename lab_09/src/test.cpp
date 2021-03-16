#include <stdio.h>

#include "Scheme.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"

void is_inside_test() {
    Scheme scheme(3);

    Circle* circle_ptr(new Circle(1, 0, 0, 1, "unit circle"));
    scheme.push_back_figure(circle_ptr);

    Figure* found1 = scheme.is_inside_figure(1, 1);    
    assert(found1 == nullptr);
    
    Rectangle* rect_ptr(new Rectangle(1, 0, 0, 4, 2));
    scheme.push_back_figure(rect_ptr);
    
    Figure* found2 = scheme.is_inside_figure(1, 1);
    assert(found2 == rect_ptr);
    
    Figure* found3 = scheme.is_inside_figure(-2, 1);
    assert(found3 == rect_ptr);

    Figure* found4 = scheme.is_inside_figure(0, 0);
    assert(found4 == circle_ptr);

    Figure* found5 = scheme.is_inside_figure(2, 2);
    assert(found5 == nullptr);

    printf("\"is_inside_test\" passed!\n");
}

int main() {
    is_inside_test();
}