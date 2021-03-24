#include "employees.hpp"

#include <string>
#include <iostream>

Employee::Employee(std::string name, int32_t base_salary)  
	: _name(name), _base_salary(base_salary) {}

Employee * Employee::readEmployee() {
	int type;
	std::cin >> type;
	std::string name;
	std::cin >> name;
	int32_t base_salary;
	std::cin >> base_salary;

	Employee * e;
	if (type == 1) {
        int _has_bonus;
        std::cin >> _has_bonus;
        e = new Developer(name, base_salary, _has_bonus);
    }

    if (type == 2) {
	    int _sold_nm, _price;
        std::cin >> _sold_nm >> _price;
        e = new SalesManager(name, base_salary, _sold_nm, _price);
    }
    return e;
}


std::ostream& operator << (std::ostream& out, Employee& e) {
	return e.print(out);
}


Developer::Developer(std::string name, int32_t base_salary, bool has_bonus)
	: Employee(name, base_salary), _has_bonus(has_bonus) {}

std::ostream& Developer::print (std::ostream& out) const {
	out << "Developer\n";
	out << "Name: " << _name << "\n";
	out << "Base salary: " << _base_salary << "\n";
	out << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
	return out;
}

SalesManager::SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price)
	: Employee(name, base_salary), _sold_nm(sold_nm), _price(price) {}
    
std::ostream& SalesManager::print (std::ostream& out) const {
	out << "Sales Manager\n";
	out << "Name: " << _name << "\n";
	out << "Base salary: " << _base_salary << "\n";
	out << "Sold items: " << _sold_nm << "\n";
	out << "Item price: " << _price << "\n";
	return out;
}

EmployeesArray::~EmployeesArray() {
	for (Employee * e : _employees) 
		delete e;
}

void EmployeesArray::add(Employee *e) {
	_employees.push_back(e);
}

int32_t EmployeesArray::total_salary() const {
	int32_t total_salary = 0;
	for (Employee * e : _employees) 
		total_salary += e -> salary();
	return total_salary;
}

std::ostream& operator << (std::ostream& out, EmployeesArray& array) {
	for (int i = 0; i < array._employees.size(); i++) {
		out << i + 1 << ". " << *(array._employees[i]); 
	}
	out << "== Total salary: " << array.total_salary() << "\n\n";
	return out;
}

