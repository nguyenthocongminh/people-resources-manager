//
//  FileIoUtils.cpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include <list>
#include <string>
#include <iostream>

#include "Employee.h"
#include "FileIoUtils.h"

using namespace std;

string FileIoUtils::_resourceFile = "./employees.txt";

list<Employee *> FileIoUtils::_employees;

const list<Employee *> FileIoUtils::listEmployee()
{
    return FileIoUtils::_employees;
};

bool FileIoUtils::addEmployee(Employee *employee){
    
    FILE  *file;
    file = fopen(FileIoUtils::_resourceFile.c_str(),"ab+");
    
    fprintf(file, "%s %s %s %s %s \n", employee->id().c_str(), employee->name().c_str(), employee->dateOfBirth().c_str(), employee->address().c_str(), employee->department().c_str());
    
    fclose(file);
    
    FileIoUtils::_employees.push_back(employee);
    return true;
}

Employee* FileIoUtils::findEmployeeById(const string &id)
{
    list<Employee *>::const_iterator it;
    for (it = _employees.begin(); it != _employees.end(); it++) {
        if ((*it)->id() ==  id ) {
            return *it;
        }
    }
    
    return nullptr;
}

void FileIoUtils::refeshData()
{
    char id[20], name[200], dateOfBirth[20], address[300], department[200];
    
    FILE  *file;
    file = fopen(FileIoUtils::_resourceFile.c_str(),"r");
    
    if (file == nullptr) {
        return;
    }
    while(
          fscanf(file, "%s %s %s %s %s", &id[0], &name[0], &dateOfBirth[0], &address[0], &department[0])!= EOF) {
        string _id(id);
        string _name(name);
        string _dateOfBirth(dateOfBirth);
        string _address(address);
        string _department(department);
        Employee *em = new Employee(_id, _name, _dateOfBirth, _address, _department);
        FileIoUtils::_employees.push_back(em);
    }
}
