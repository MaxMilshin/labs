#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <vector>
#include <iostream>

class Employee {
public:
    Employee(int type, char* name, int32_t base_salary);
    virtual ~Employee();

    virtual int32_t salary() const = 0;

    static Employee * createEmployee(std::istream&); 
    friend std::istream& operator >> (std::istream&, Employee *);
    
    static Employee * createEmployee(std::ifstream&);
    friend std::ifstream& operator >> (std::ifstream&, Employee *);
    
    friend std::ostream& operator << (std::ostream&, Employee *);

    friend std::ofstream& operator << (std::ofstream&, Employee *);

protected:
    virtual std::istream& read(std::istream&);
    virtual std::ifstream& load(std::ifstream&);

    virtual std::ostream& print (std::ostream&) const;
    virtual std::ofstream& save (std::ofstream&) const;

private:
    static const int MAX_NAME_LENGTH = 110;
    
protected:
    int _type;
    char* _name;
    int32_t _base_salary;
};


class Developer : public Employee {
public:
    int32_t salary() const override {
        int32_t salary = _base_salary;
        if (_has_bonus) { salary += 1000; }
            return salary;
    }

    Developer(int type, char* name = nullptr, int32_t base_salary = 0, bool has_bonus = false);
    ~Developer() = default;

protected:
    std::istream& read(std::istream&) override;
    std::ifstream& load(std::ifstream&) override;

    std::ostream& print (std::ostream&) const override;
    std::ofstream& save (std::ofstream&) const override;

protected:
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    int32_t salary() const override {
        return _base_salary + _sold_nm * _price * 0.01;
    }
    
    SalesManager(int type, char* name = nullptr, int32_t base_salary = 0, int32_t sold_nm = 0, int32_t price = 0);
    ~SalesManager() = default;

protected:
    std::istream& read(std::istream&) override;
    std::ifstream& load(std::ifstream&) override;

    std::ostream& print (std::ostream&) const override;
    std::ofstream& save (std::ofstream&) const override;

protected:
    int32_t _sold_nm, _price;
};


class EmployeesArray {
public:
    EmployeesArray() = default;
    ~EmployeesArray();

    void add(Employee *e);
    int32_t total_salary() const;

    friend std::ofstream& operator << (std::ofstream&, EmployeesArray&);
    friend std::ostream& operator << (std::ostream&, EmployeesArray&);
    friend std::ifstream& operator >> (std::ifstream&, EmployeesArray&);

private:
    std::vector<Employee *> _employees;
};

#endif