#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <memory>
#include <vector>

#include "matrix.hpp"

const int MAX_COMMAND_LEN = 20;
const int REGISTERS_COUNT = 10;

int num(std::string reg) {
	return int(reg[1]) - int('0');
}

int main() {
	Matrix registers[REGISTERS_COUNT];
	
	while (true) {
		try {
			char command[MAX_COMMAND_LEN];
			std::cin >> command;
			std::string reg1, reg2;
			if (strcmp(command, "load") == 0) {
				std::string filename;
				std::cin >> reg1 >> filename;
				std::ifstream in(filename, std::ios::in);
				if (!in.is_open()) {
					std::cout << "LOAD: unable to open file." << std::endl;
					continue;
				}
				Matrix::load(registers[num(reg1)], in);
			}
			if (strcmp(command, "print") == 0) {
				std::cin >> reg1;
				registers[num(reg1)].print();
			}
			if (strcmp(command, "add") == 0) {
				std::cin >> reg1 >> reg2;
				registers[num(reg1)].add(registers[num(reg2)]);
			}
			if (strcmp(command, "mul") == 0) {
				std::cin >> reg1 >> reg2;
				registers[num(reg1)].multiply(registers[num(reg2)]);
			}
			if (strcmp(command, "elem") == 0) {
				int row, col;
				std::cin >> reg1 >> row >> col;
				std::cout << registers[num(reg1)].get_element(row, col) << std::endl;
			}
			if (strcmp(command, "exit") == 0) {
				break;
			}
		} catch (const MatrixException& e) {
			std::cout << e.get_message() << std::endl;
		} catch (const std::bad_alloc& e) {
			std::cout << "Unable to allocate memory." << std::endl;
		}
	}
	
	
	return 0;
}