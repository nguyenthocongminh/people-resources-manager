//
//  EmployeeManager.cpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include <string>
#include <iostream>
#include "Employee.h"
#include "EmployeeManager.h"
#include "FileIoUtils.h"

using namespace std;

EmployeeManager::EmployeeManager()
{
    
}
EmployeeManager *EmployeeManager::_instance = nullptr;

EmployeeManager *EmployeeManager::instance()
{
    if (_instance == nullptr) {
        _instance = new EmployeeManager();
    }

    return _instance;
}

void EmployeeManager::insertEmployee()
{
    string id;
    string name;
    string dateOfBirth;
    string address;
    string department;
    
    cout << "\n Nhap id: ";
    cin >> id;
    
    cout << "\n Nhap ten: ";
    cin >> name;
    
    cout << "\n Nhap ngay sinh: ";
    cin >> dateOfBirth;
    
    cout << "\n Nhap dia chi: ";
    cin >> address;
    
    cout << "\n Nhap phong ban: ";
    cin >> department;
    
    Employee *employee = new Employee(id, name, dateOfBirth, address, department);
    
    FileIoUtils::addEmployee(employee);
    
}

void EmployeeManager::findEmployeeById()
{
    string id;
    cout << "\nNhap id: ";
    cin >> id;
    
    Employee *employee = FileIoUtils::findEmployeeById(id);
    if(employee != nullptr) {
        employee->printInfo();
    } else {
        cout << "Khong tim thay nhan vien id = " << id << "\n";
    }
}

void EmployeeManager::printEmployees()
{
    list<Employee *> employees = FileIoUtils::listEmployee();
    list<Employee *>::const_iterator it;
    for (it = employees.begin(); it != employees.end(); it++) {
        (*it)->printInfo();
    }
}
