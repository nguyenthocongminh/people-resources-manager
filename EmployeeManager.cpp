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
#include "ValidateUtils.h"

using namespace std;

EmployeeManager::EmployeeManager()
{
    this->refeshData();
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
    
    cin.get();
    
    cout << "\nNhap id: ";
    getline(cin, id);
    
    cout << "\nNhap ten: ";
    getline(cin, name);
    
    cout << "\nNhap ngay sinh: ";
    getline(cin, dateOfBirth);
    
    cout << "\nNhap dia chi: ";
    getline(cin, address);
    
    cout << "\nNhap phong ban: ";
    getline(cin, department);
    
    Employee *employee = new Employee(id, name, dateOfBirth, address, department);
    
    list<string> validate = ValidateUtils::validateEmployee(*employee, _employees);
    
    if(validate.empty()){
        FileIoUtils::addEmployee(employee);
        this->_employees.push_back(*employee);
        return;
    }
    
    ValidateUtils::printValid(validate);
    cout << "Nhan Enter de tiep tuc\n";
    cin.get();
}

void EmployeeManager::findEmployeeById()
{
    string id;
    cout << "\nNhap id: ";
    cin >> id;
    
    list<Employee>::const_iterator it;
    for (it = _employees.begin(); it != _employees.end(); it++) {
        if (it->id() ==  id ) {
            it->printInfo();
            return;
        }
    }
    
    cout << "Khong tim thay nhan vien id = " << id << "\n";
}

void EmployeeManager::printEmployees()
{
    cout<<"\n----------------------------------------------------------------------------";
    cout<<"\n ID     |     TEN     |     NGAYSINH     |     DIA CHI     |     PHONG";
    cout<<"\n----------------------------------------------------------------------------\n";
    
    list<Employee>::const_iterator it;
    for (it = _employees.begin(); it != _employees.end(); it++)
    {
        it->printInfo();
    }
}

void EmployeeManager::refeshData()
{
    _employees.clear();
    FileIoUtils::loadAllEmployee(_employees);
}
