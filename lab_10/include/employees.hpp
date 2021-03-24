#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <vector>
#include <iostream>

class Employee {
public:
    Employee(std::string name, int32_t base_salary);
    virtual ~Employee() = default;

    virtual int salary() const = 0;

    static Employee * readEmployee();

    virtual std::ostream& print (std::ostream&) const = 0;
    friend std::ostream& operator << (std::ostream&, Employee&);

protected:
    std::string _name;
    int32_t _base_salary;
};


class Developer : public Employee {
public:
    int salary() const override {
        int salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
            return salary;
    }

    Developer(std::string name, int32_t base_salary, bool has_bonus);
    ~Developer() = default;

    std::ostream& print (std::ostream&) const override;

  /* ?? operator<<(??); */
private:
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    int salary() const override {
        return _base_salary + _sold_nm * _price * 0.01;
    }

    SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price);
    ~SalesManager() = default;

    std::ostream& print (std::ostream&) const override;
    /* ?? operator>>(??); */
    /* ?? operator<<(??); */
private:
    int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray();

    void add(Employee *e);
    int32_t total_salary() const;

    friend std::ostream& operator << (std::ostream&, EmployeesArray&);
private:
    std::vector<Employee *> _employees;
};

#endif