#ifndef Employee_H
#define Employee_H

#include <string>
using namespace std;


class Employee {
    friend class EmployeeBuilder;

private:
    string _id;
    string _name;
    string _dateOfBirth;
    string _address;
    string _department;

public:
    Employee(const string &id,
             const string &name,
             const string &dateOfBirth,
             const string &address,
             const string &department);

public:
    bool validate() const;
    
    const string &id() const;
    const string &name() const;
    const string &dateOfBirth() const;
    const string &address() const;
    const string &department() const;
    
    void printInfo() const;
};


#endif // Employee_H
