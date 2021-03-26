#include <iostream>
#include <fstream>

#include "employees.hpp"

const int MAX_LENGTH_OF_COMMAND = 10;

int main() {
	EmployeesArray employees;
    while (true) {
        char s[MAX_LENGTH_OF_COMMAND];
        std::cin >> s;
        if (strcmp(s, "add") == 0) {
            Employee * e = Employee::createEmployee(std::cin);
            std::cin >> e;
        	employees.add(e);
        }
        if (strcmp(s, "list") == 0) {
            std::cout << employees;
        }
        if (strcmp(s, "load") == 0) {
            std::string filename;
            std::cin >> filename;
            std::ifstream in(filename, std::ios::binary);
            in >> employees;
            in.close();
        }
        if (strcmp(s, "save") == 0) {
            std::string filename;
            std::cin >> filename;
            std::ofstream out(filename, std::ios::binary);
            out << employees;
            out.close();
        }
        if (strcmp(s, "exit") == 0) {
            break;
        }
    }
}
