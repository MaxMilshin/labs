#include <iostream>

#include "employees.hpp"

int main() {
	EmployeesArray employees;
    while (true) {
        char s[20];
        std::cin >> s;
        if (strcmp(s, "add") == 0) {
        	employees.add(Employee::readEmployee());
        }
        if (strcmp(s, "list") == 0) {
            std::cout << employees;
        }
        if (strcmp(s, "load") == 0) {
            // TODO()
        }
        if (strcmp(s, "save") == 0) {
            // TODO()
        }
        if (strcmp(s, "exit") == 0) {
            break;
        }
    }
}
