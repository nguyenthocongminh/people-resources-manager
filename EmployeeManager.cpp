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


void EmployeeManager::importCsv()
{
    cin.get();
    cout << "Nhap file import: " << endl;
    string path;
    getline(cin, path);
    if(!FileIoUtils::checkExist(path)){
        cout << "File khong ton tai !\n";
        return;
    }
    list<Employee> employees = FileIoUtils::readEmployeeFromCsv(path);
    
    bool flagErr = false;
    
    list<Employee>::const_iterator it;
    for (it = employees.begin(); it != employees.end(); it++) {
        list<string> validate = ValidateUtils::validateEmployee(*it, _employees);
        if(!validate.empty()){
            flagErr = true;
            cout << "------------------\n";
            cout << "Co loi tai dong: ";
            it -> printInfo();
            ValidateUtils::print(validate);
            cout << "------------------\n";
        }
        
    }
    if(!flagErr){
        FileIoUtils::addListEmployees(employees);
        this->_employees.insert(_employees.end(), employees.begin(), employees.end());
        cout << "=======\nTong so nhan vien import thanh cong: " << employees.size() << endl;
    }
}

void EmployeeManager::refeshData()
{
    _employees.clear();
    FileIoUtils::loadAllEmployee(_employees);
}
