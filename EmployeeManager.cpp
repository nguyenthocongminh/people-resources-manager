//
//  EmployeeManager.cpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include <string>
#include <iostream>
#include <ctime>

#include "Employee.h"
#include "EmployeeManager.h"
#include "FileIoUtils.h"
#include "ValidateUtils.h"
#include "CheckPoint.h"

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
            
            list<CheckPoint> allCheckpoints = FileIoUtils::loadCheckPoint(it->id());
            time_t now = time(0);
            tm *ltm = localtime(&now);
            
            list<CheckPoint> checkpoints = this->filterByMonth(allCheckpoints, 1 + ltm->tm_mon, ltm->tm_year);
            
            this->printCheckPointSortByDay(checkpoints);
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

void EmployeeManager::addCheckPoint()
{
    string employeeId;
    cout << "\nNhap id nhan vien: ";
    cin >> employeeId;
    
    string date, status;
    cout << "Nhap ngay diem danh (0 de tro lai menu): ";
    cin >> date;
    while (date != "0" && !ValidateUtils::validateDate(date)) {
        cout << "Ngay sai dinh dang, nhap lai: ";
        cin >> date;
    }
    if (date == "0") {
        return;
    }
    
    cout << "Nhap trang thai (0 de tro lai menu): ";
    cin >> status;
    while (status != "0" && !ValidateUtils::validateStatus(status)) {
        cout << "Trang thai sai dinh dang, nhap lai: ";
        cin >> status;
    }
    if (status == "0") {
        return;
    }
    
    CheckPoint *cp = new CheckPoint(employeeId, date, status);
    
    // Rewrite when exist check point
    list<CheckPoint> checkpoints = FileIoUtils::loadCheckPoint(employeeId);
    list<CheckPoint>::const_iterator itcp;
    for (itcp = checkpoints.begin(); itcp != checkpoints.end(); itcp++) {
        if(itcp->employeeId().compare(employeeId) == 0
           && itcp->date().compare(date) == 0){
            checkpoints.erase(itcp);
            checkpoints.push_back(*cp);
            break;
        }
    }
    
    this->printCheckPointSortByDay(checkpoints);
    FileIoUtils::addCheckPoint(*cp);
}

list<CheckPoint> & EmployeeManager::filterByMonth(list<CheckPoint> & checkpoints, int month, int year)
{
    static list<CheckPoint> result;
    result.insert(result.end(), checkpoints.begin(), checkpoints.end()); // TODO: filter by month here
    return checkpoints;
}

void EmployeeManager::printCheckPointSortByDay(list<CheckPoint> &checkpoints)
{
    // TODO: replace logic: print checkpoint date + value in sorted day
    list<CheckPoint>::const_iterator itcp;
    for (itcp = checkpoints.begin(); itcp != checkpoints.end(); itcp++) {
        itcp->printValue();
    }
}

void EmployeeManager::refeshData()
{
    _employees.clear();
    FileIoUtils::loadAllEmployee(_employees);
}
