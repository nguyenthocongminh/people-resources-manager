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
#include <regex>

using namespace std;

Employee::Employee(const string &id,
                   const string &name,
                   const string &dateOfBirth,
                   const string &address,
                   const string &department)
: _id(id), _name(name), _dateOfBirth(dateOfBirth), _address(address), _department(department)
{
}

bool Employee::validate() const {
    int count_e = 0;
    if (_id.empty()) {
        count_e++;
        cout << "ID khong duoc de trong" << endl;
    }
    if (_name.empty()) {
        count_e++;
        cout << "Ten khong duoc de trong" << endl;
    }
    regex date("^([0-2][0-9]|(3)[0-1])(\\/)(((0)[0-9])|((1)[0-2]))(\\/)\\d{4}$");
    if (!regex_match(_dateOfBirth, date)) {
        count_e++;
        cout << "Ngay sinh khong dung dinh dang" << endl;
    }
    if (_address.empty()) {
        count_e++;
        cout << "Dia chi khong duoc de trong" << endl;
    }
    if (_department.empty()) {
        count_e++;
        cout << "Bo phan cong tac khong duoc de trong" << endl;
    }
    if (count_e > 0) {
        return false;
    }
    return true;
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
    cout << _id << "\t\t" << _name << "\t\t" << _dateOfBirth << "\t\t"
    << _address << "\t\t" << _department << "\n" << endl;
}
