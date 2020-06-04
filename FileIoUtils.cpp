//
//  FileIoUtils.cpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include <list>
#include <string>
#include "Employee.h"
#include "FileIoUtils.h"

string FileIoUtils::_resourceFile = "./employees.txt";

list<Employee> FileIoUtils::_employees;

const list<Employee> &FileIoUtils::listEmployee()
{
//    TODO: read from file
    return _employees;
};

bool FileIoUtils::addEmployee(Employee &employee){
//    TODO: write into file
    _employees.push_back(employee);
    return true;
}

Employee FileIoUtils::findEmployeeById(string &id)
{
//    TODO: get imployee from file
    Employee *employee = new Employee(id, "name", "dobirth", "", "");
    return *employee;
}
