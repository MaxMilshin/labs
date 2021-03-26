#include <iostream>

#include "Scheme.hpp"

Scheme::Scheme(int capacity) : figures_(new Figure*[capacity]) {}
Scheme::~Scheme() {
	for (std::size_t i = 0; i < sz; i++) 
		delete figures_[i];
	delete [] figures_;
}

std::size_t Scheme::get_figure_index(int id) {
	std::size_t index = 0;
	while (index < sz && figures_[index]->get_id() != id) 
		index++;
	return index;
}

void Scheme::push_back_figure(Figure* fg) {
	figures_[sz++] = fg;
}

void Scheme::remove_figure(int id) {
	std::size_t index = get_figure_index(id);
	if (index != sz) {
		std::swap(figures_[index], figures_[sz - 1]);
		delete figures_[--sz];
	}
}

void Scheme::print_all_figures() {
	for (std::size_t i = 0; i < sz; i++) 
		figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
	std::size_t index = get_figure_index(id);
	if (index != sz)
		figures_[index]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) {
	std::size_t i = 0;
	while (i < sz && !(figures_[i]->is_inside(x, y)))
		i++;
	return (i != sz) ? figures_[i] : nullptr;
}

void Scheme::move(int id, int new_x, int new_y) {
	std::size_t index = get_figure_index(id);
	if (index != sz)
		figures_[index]->move(new_x, new_y);
}

