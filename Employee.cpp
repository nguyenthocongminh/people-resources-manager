//
//  Employee.cpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include "Employee.h"
#include <string>
#include <iostream>

using namespace std;

Employee::Employee(const string &id,
                   const string &name,
                   const string &dateOfBirth,
                   const string &address,
                   const string &department)
: _id(id), _name(name), _dateOfBirth(dateOfBirth), _address(address), _department(department)
{
}

const string &Employee::id() const
{
    return _id;
}
const string &Employee::name() const
{
    return _name;
}
const string &Employee::dateOfBirth() const
{
    return _dateOfBirth;
}
const string &Employee::address() const
{
    return _address;
}
const string &Employee::department() const
{
    return _department;
}

void Employee::printInfo() const
{
    cout << _id << " - " << _name << " - " << _dateOfBirth << " - "
    << _address << " - " << _department << std::endl;
}
