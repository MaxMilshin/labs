#include <stdexcept>
#include <string.h>
#include "my_array.hpp"

using lab_13::my_array;

const std::size_t SZ = 10;

void fill_test() {
	my_array<int, SZ> int_arr;
	
	int_arr.fill(239);
	for (std::size_t i = 0; i < SZ; i++) {
		assert(int_arr[i] == 239);
	}

	int_arr.fill(123);
	for (std::size_t i = 0; i < SZ; i++) {
		assert(int_arr[i] == 123);
	}

	struct Point {
		Point(int x = 0, int y = 0): x(x), y(y) {}
		int x, y;
	};

	my_array<Point, SZ> point_arr;
	point_arr.fill(Point(111, 222));
	for (std::size_t i = 0; i < SZ; i++) {
		assert(point_arr[i].x == 111 && point_arr[i].y == 222);
	}

	std::cout << "fill_test has passed!" << std::endl;
}

void at_test() {
	my_array<int, SZ> int_arr;
	
	int_arr.fill(239);
	for (std::size_t i = 0; i < SZ; i++) {
		assert(int_arr.at(i) == 239);
	}
	
	try {
		int_arr.at(10);
	} catch (std::out_of_range const &e)  {
		std::cout << "at_test has passed!" << std::endl;
		return;
	}
	
	std::cout << "at_test has failed!!!!!!!" << std::endl;
}

void empty_and_size_test() {
	my_array<std::string, SZ> string_arr;
	assert(string_arr.size() == SZ && !string_arr.empty());

	my_array<std::string, 0> empty_string_arr;
	assert(empty_string_arr.size() == 0 && empty_string_arr.empty());

	std::cout << "empty_and_size_test has passed" << std::endl;
}

void bool_specialization_test() {
	my_array<bool, SZ> arr;
	assert(arr.size() == SZ && !arr.empty());
	
	arr.fill(true);
	for (std::size_t i = 0; i < SZ; i++) {
		assert(arr[i] == true);
	}

	for (std::size_t i = 0; i < SZ; i += 3) {
		arr[i] = false;
	}

	for (std::size_t i = 0; i < SZ; i++) {
		assert(arr.at(i) == (i % 3 == 0) ? false : true);
	}

	try {
		arr.at(10) = true;
	} catch (std::out_of_range const &e)  {
		std::cout << "bool_specialization_test has passed!" << std::endl;
		return;
	}

	std::cout << "bool_specialization_test has failed!!!!!!!" << std::endl;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		fill_test();
		at_test();
		empty_and_size_test();
		bool_specialization_test();
		return 0;
	}
	if (strcmp(argv[1], "fill_test") == 0) {
		fill_test();
	}
	if (strcmp(argv[1], "at_test") == 0) {
		at_test();
	}
	if (strcmp(argv[1], "empty_and_size_test") == 0) {
		empty_and_size_test();
	}
	if (strcmp(argv[1], "bool_specialization_test") == 0) {
		bool_specialization_test();
	}

	return 0;
}