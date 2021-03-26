#include "employees.hpp"

#include <string>
#include <iostream>
#include <fstream>


// ____________________________________________________________________________________
// ________Employee____________________________________________________________________________

Employee::Employee(int type, char* name, int32_t base_salary) 
	: _type(type), _name(name), _base_salary(base_salary) {
}

Employee::~Employee() {
	delete [] _name;
}


Employee * Employee::createEmployee(std::istream& in) {
	int type;
	in >> type;
	if (type == 1) 
		return new Developer(type); 
	return new SalesManager(type);
}

std::istream& operator >> (std::istream& in, Employee *e) {
	return e->read(in);
}

std::istream& Employee::read(std::istream& in) {
	char name[MAX_NAME_LENGTH];
	in >> name >> _base_salary;
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);	
	return in;
}


Employee * Employee::createEmployee(std::ifstream& in) {
	int type;
	in.read(reinterpret_cast<char*>(&type), sizeof type);
	if (type == 1) 
		return new Developer(type); 
	return new SalesManager(type);	
}

std::ifstream& operator >> (std::ifstream& in, Employee *e) {
	return e->load(in);
}

std::ifstream& Employee::load(std::ifstream& in) {
	char name[MAX_NAME_LENGTH];
	in.getline(name, MAX_NAME_LENGTH, '\0');
	_name = new char[strlen(name) + 1];
	strcpy(_name, name);	
	in.read(reinterpret_cast<char*>(&_base_salary), sizeof _base_salary);
	return in;
}


std::ostream& operator << (std::ostream& out, Employee* e) {
	return e->print(out);
}

std::ostream& Employee::print (std::ostream& out) const {
	out << ((_type == 1) ? "Developer" : "SalesManager") << "\n";
	out << "Name: " << _name << "\n";
	out << "Base Salary: " << _base_salary << "\n";
	return out;
}

std::ofstream& operator << (std::ofstream& out, Employee* e) {
	return e->save(out);
}

std::ofstream& Employee::save (std::ofstream& out) const {
	out.write(reinterpret_cast<const char*>(&_type), sizeof _type);
	out.write(_name, strlen(_name) + 1); 
	out.write(reinterpret_cast<const char*>(&_base_salary), sizeof _base_salary);
	return out;
}

// ________________________________________________________________________________________________________________________
// ________Developer_____________________________________________________________________________________________________________


Developer::Developer(int type, char* name, int32_t base_salary, bool has_bonus)
	: Employee(type, name, base_salary), _has_bonus(has_bonus) {}

std::istream& Developer::read(std::istream& in) {
	Employee::read(in);
    in >> _has_bonus;
	return in;
}

std::ifstream& Developer::load(std::ifstream& in) {
	Employee::load(in);
    in.read(reinterpret_cast<char*>(&_has_bonus), sizeof _has_bonus);
	return in;
}

std::ostream& Developer::print (std::ostream& out) const {
	Employee::print(out);
	out << "Has bonus: " << (_has_bonus ? "+" : "-") << "\n";
	return out;
}

std::ofstream& Developer::save (std::ofstream& out) const {
	Employee::save(out);
	out.write(reinterpret_cast<const char*>(&_has_bonus), sizeof _has_bonus);
	return out;
}

// _________________________________________________________________________________________________________________
// _______SalesManager_________________________________________________________________________________


SalesManager::SalesManager(int type, char* name, int32_t base_salary, int32_t sold_nm, int32_t price)
	: Employee(type, name, base_salary), _sold_nm(sold_nm), _price(price) {}

std::istream& SalesManager::read(std::istream& in) {
	Employee::read(in);
    in >> _sold_nm >> _price;
	return in;
}
 
std::ifstream& SalesManager::load(std::ifstream& in) {
	Employee::load(in);
    in.read(reinterpret_cast<char*>(&_sold_nm), sizeof _sold_nm);
	in.read(reinterpret_cast<char*>(&_price), sizeof _price);	
	return in;
}    

std::ostream& SalesManager::print (std::ostream& out) const {
	Employee::print(out);
	out << "Sold items: " << _sold_nm << "\n";
	out << "Item price: " << _price << "\n";
	return out;
}

std::ofstream& SalesManager::save (std::ofstream& out) const {
	Employee::save(out);
	out.write(reinterpret_cast<const char*>(&_sold_nm), sizeof _sold_nm);
	out.write(reinterpret_cast<const char*>(&_price), sizeof _price);
	return out;
}

// ____________________________________________________________________________________
// _______EmployeesArray_________________________________________________


EmployeesArray::~EmployeesArray() {
	for (Employee *e : _employees) 
		delete e;
}

void EmployeesArray::add(Employee *e) {
	_employees.push_back(e);
}

int32_t EmployeesArray::total_salary() const {
	int32_t total_salary = 0;
	for (Employee * e : _employees) 
		total_salary += e->salary();
	return total_salary;
}

std::ostream& operator << (std::ostream& out, EmployeesArray& array) {
	for (size_t i = 0; i < array._employees.size(); i++) {
		out << i + 1 << ". " << array._employees[i]; 
	}
	out << "== Total salary: " << array.total_salary() << "\n\n";
	return out;
}

std::ofstream& operator << (std::ofstream& out, EmployeesArray& array) {
	int size = array._employees.size();
	out.write(reinterpret_cast<char*>(&size), sizeof size);
	for (size_t i = 0; i < size; i++) {
		out << array._employees[i];
	}
	return out;
}

std::ifstream& operator >> (std::ifstream& in, EmployeesArray& array) {
	int size;
	in.read(reinterpret_cast<char*>(&size), sizeof size);
	for (size_t i = 0; i < size; i++) {
		Employee *e = Employee::createEmployee(in);
		in >> e;
		array.add(e);
	}
	return in;
}
