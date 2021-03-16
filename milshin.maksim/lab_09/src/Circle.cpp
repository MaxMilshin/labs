#include <iostream>

#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char* label)
	: Figure(id, x, y), radius(radius), label(new const char*(label)) {}

Circle::~Circle() {
	delete label;
}

void Circle::print() const {
	printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, *label);
}

bool Circle::is_inside(int x, int y) const {
	return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) < radius * radius; 
}

void Circle::zoom(int factor) {
	radius *= factor;
}