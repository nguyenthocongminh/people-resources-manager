//
//  EmployeeManager.cpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include <string>
#include <list>
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <thread>
#include <future>
#include <vector>

#include "Employee.h"
#include "EmployeeDTO.h"
#include "EmployeeManager.h"
#include "FileIoUtils.h"
#include "ValidateUtils.h"
#include "CheckPoint.h"
#include "DateUtils.h"
#include "StringUtils.h"

using namespace std;
using namespace std::chrono;

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
            
            list<CheckPoint> checkpoints = filterByMonth(allCheckpoints, 1 + ltm->tm_mon, ltm->tm_year + 1900);
            
            printCheckPointSortByDay(checkpoints, 1 + ltm->tm_mon, ltm->tm_year + 1900);
            return;
        }
    }
    
    cout << "Khong tim thay nhan vien id = " << id << "\n";
}

void EmployeeManager::searchByName()
{
    string name;
    cout << "\nNhap ten: ";
    cin >> name;
    
    bool exist = false;
    
    list<Employee>::const_iterator it;
    for (it = _employees.begin(); it != _employees.end(); it++) {
        if (StringUtils::containIgnoreCase(it->name(), name)) {
            it->printInfo();
            exist= true;
        }
    }
    
    if(!exist){
        cout << "Khong tim thay nhan vien ten = " << name << "\n";
    }
}

void EmployeeManager::checkpointHistory()
{
    int month;
    cout << "\nNhap thang: ";
    cin >> month;
    
    int year;
    cout << "\nNhap nam: ";
    cin >> year;
    
    string option;
    cout << "\nNhap chuc nang 1-Theo nhan vien; 2-Theo bo phan; 3-Tat ca: ";
    cin >> option;
    
    string textSearch;
    if(option == "1") {
        cout << "\nNhap id: ";
        cin >> textSearch;
    }
    if(option == "2") {
        cout << "\nNhap bo phan: ";
        cin >> textSearch;
    }
        
    if(_employees.size() <= 0) {
        cout << "Khong co nhan vien nao !\n";
        return;
    }
    
    bool exist = false;
    list<Employee> employees;
    
    list<Employee>::const_iterator it;
    
    if(option == "3"){
        employees = _employees;
        exist = true;
    }else{
        for (it = _employees.begin(); it != _employees.end(); it++) {
            // TODO: 02 filter by textSearch and option here
            exist = true;
            employees.push_back(*it);
        }
    }
    
    list<EmployeeDTO> employeeDtos;
    
    if(exist){
        cout << "------\n";
        auto start = high_resolution_clock::now();
        
        for (it = employees.begin(); it != employees.end(); it++) {
            list<CheckPoint> cps = filterByMonth(FileIoUtils::loadCheckPoint((*it).id()), month, year);
            (*it).printInfo();
            printCheckPointSortByDay(cps, month, year);
            cout << "------\n";
            
            EmployeeDTO *emDto = new EmployeeDTO((*it).id(), (*it).name(), (*it).department(), cps);
            employeeDtos.push_back(*emDto);
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time to read in microseconds: " << duration.count() << "\n";
    }
    
    if(!exist){
        cout << "Khong tim thay ket qua nao;\n";
        cout << "Thang: " << month << "/" << year << ";\n";
        if(option == "1") {
            cout << "1-Theo nhan vien;\n";
        }
        if(option == "2") {
            cout << "2-Theo bo phan;\n";
        }
        if(option == "2" || option == "1") {
            cout << "Tim kiem: " << textSearch << ";\n";
        }
    }
    if(exist) {
        string csvOption;
        cout << "Ban co muon xuat ket qua ra .csv Y/N ?";
        cin >> csvOption;
        if (csvOption == "Y" || csvOption == "y") {
            cout << "Xuat file: " << FileIoUtils::genCheckpointHistory(employeeDtos, month, year);
        }
    }
}

void EmployeeManager::readFileByThread(promise<list<EmployeeDTO>> && promise, vector<Employee> employees, int month, int year)
{
    list<EmployeeDTO> dtos;
    
    for(auto em : employees) {
        list<CheckPoint> cps = filterByMonth(FileIoUtils::loadCheckPoint(em.id()), month, year);
        EmployeeDTO *dto = new EmployeeDTO(em.id(), em.name(), em.department(), cps);
        dtos.push_back(*dto);
    }
    
    promise.set_value(dtos);
}

void EmployeeManager::checkpointHistoryMultiThread()
{
    int month;
    cout << "\nNhap thang: ";
    cin >> month;
    
    int year;
    cout << "\nNhap nam: ";
    cin >> year;
    
    string option;
    cout << "\nChuc nang demo cho multiple thread option = 3-Tat ca:\n";
    
    cout << "------\n";
    auto start = high_resolution_clock::now();
    
    if(_employees.size() <= 0) {
        cout << "Khong co nhan vien nao !\n";
        return;
    }
    
    int sizeHandle = 500;
    long splitNum = (_employees.size() + sizeHandle - 1) / sizeHandle; // To round up, handle 500 employee in a thread
    
    thread threads[splitNum];
    future<list<EmployeeDTO>> futures[splitNum];
    
    vector<Employee> copyEmployees(_employees.begin(), _employees.end());
    
    for(int i = 0; i < splitNum; i++) {
        vector<Employee> empls(copyEmployees.begin() + sizeHandle * i, copyEmployees.begin() + sizeHandle * (i + 1));
        promise<list<EmployeeDTO>> promiseHandle;
        futures[i] = promiseHandle.get_future();
        
        threads[i] = thread(&EmployeeManager::readFileByThread, *this, move(promiseHandle), empls, month, year);
    }
    vector<list<EmployeeDTO>> employeeDtosVector;
    
    for(int i = 0; i < splitNum; i++) {
        
        list<EmployeeDTO> employeeDtos;
        list<EmployeeDTO>::const_iterator itDto;
        employeeDtos = futures[i].get();
        
        for (itDto = employeeDtos.begin(); itDto != employeeDtos.end(); itDto++) {
            itDto->printInfo();
            printCheckPointSortByDay(itDto->checkpoints(), month, year);
            cout << "------\n";
        }
        employeeDtosVector.push_back(employeeDtos);
    }

    for(auto i = 0; i < splitNum; i++) {
        threads[i].join();
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time to read in microseconds: " << duration.count() << "\n";
    
    string csvOption;
    cout << "Ban co muon xuat ket qua ra .csv Y/N ?";
    cin >> csvOption;
    if (csvOption == "Y" || csvOption == "y") {
        cout << "Xuat file: " << FileIoUtils::genCheckpointHistoryMulti(employeeDtosVector, month, year);
    }
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

    list<CheckPoint> checkpoints = FileIoUtils::loadCheckPoint(employeeId);
    list<CheckPoint>::const_iterator itcp;
    for (itcp = checkpoints.begin(); itcp != checkpoints.end(); itcp++) {
        if(itcp->employeeId().compare(employeeId) == 0
           && itcp->date().compare(date) == 0){
            string option = "Y";
            cout << "Ngay nay da co thong tin, ban co muon cap nhat khong Y/N ?";
            cin >> option;
            if (option == "Y" || option == "y") {
                checkpoints.erase(itcp);
                checkpoints.push_back(*cp);
                FileIoUtils::rewriteCheckPoint(employeeId, checkpoints);
            }

            return;
        }
    }
    FileIoUtils::addCheckPoint(*cp);
}

list<CheckPoint> EmployeeManager::filterByMonth(const list<CheckPoint> & checkpoints, int month, int year)
{
    list<CheckPoint> result;
    list<CheckPoint>::const_iterator itcp;
    for (itcp = checkpoints.begin(); itcp != checkpoints.end(); itcp++) {
        stringstream s(itcp->date());
        string list[3];
        string tmp;
        int i = 0;
        while (getline(s, tmp, '/') && i < 3) {
            list[i++] = tmp;
        }
        int monthCP, yearCP;
        istringstream(list[1]) >> monthCP;
        istringstream(list[2]) >> yearCP;
        if (month == monthCP && year == yearCP) {
            result.push_back(*itcp);
        }
    }
    return result;
}

void EmployeeManager::printCheckPointSortByDay(const list<CheckPoint> &checkpoints, int month, int year)
{
    
//    checkpoints.sort();
    int numberOfDays = DateUtils::getNumberOfDays(month, year);
    
    list<CheckPoint>::const_iterator itcp;
    
    string monthStr = month >= 10 ? to_string(month) : "0" + to_string(month);
    cout << "Diem danh thang " << monthStr + "/" + to_string(year) << ":\n";
    
    for(int i = 1; i <= numberOfDays; i++){
        string dayStr = i >= 10 ? to_string(i) : "0" + to_string(i);
        string dateStr = dayStr + "/" + monthStr + "/" + to_string(year);
        
        cout << dateStr + ": ";
        
        string status = "-1xozoOo";
        for (itcp = checkpoints.begin(); itcp != checkpoints.end(); itcp++) {
            if(dateStr.compare(itcp->date()) == 0) {
                cout << setw(2) << itcp->value() << ";" << "\t";
                
                status = itcp->value();
                break;
            }
        }
        if(status == "-1xozoOo"){
            cout << setw(2) << "X" << ";" << "\t";
        }
        if(i % 10 == 0) {
            cout << "\n";
        }
    }
}
void EmployeeManager::genCheckpointSampleData()
{
    string months;
    int year;
    cout << "Nhap thang, cach nhau boi dau phay (,):\n";
    cin >> months;
    cout << "Nhap nam:\n";
    cin >> year;
    
    string month;
    vector<string> monthVector;
    
    stringstream strStream(months);
    while (getline(strStream, month, ',')) {
        monthVector.push_back(month);
    }
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currenMonth = ltm->tm_mon + 1;
    int currentYear = ltm->tm_year + 1900;
    
    if(currentYear < year){
        cout << "\n" << year << " > " << currentYear << endl;;
        return;
    }
    
    list<Employee>::const_iterator it;
    for (it = _employees.begin(); it != _employees.end(); it++) {
        list<CheckPoint> checkpoints;
        
        for(auto m : monthVector) {
            if(stoi(m) > currenMonth) {
                break;
            }
            
            int numberOfDays = DateUtils::getNumberOfDays(stoi(m), year);
            
            list<CheckPoint>::const_iterator itcp;
            
            string monthStr = stoi(m) >= 10 ? m : "0" + m;
            
            for(int i = 1; i <= numberOfDays; i++){
                string dayStr = i >= 10 ? to_string(i) : "0" + to_string(i);
                string dateStr = dayStr + "/" + monthStr + "/" + to_string(year);
                
                CheckPoint *cp = new CheckPoint(it->id(), dateStr, "DL");
                checkpoints.push_back(*cp);
            }
        }
        
        FileIoUtils::appendCheckPoint(it->id(), checkpoints);
    }
    
}
void EmployeeManager::refeshData()
{
    _employees.clear();
    FileIoUtils::loadAllEmployee(_employees);
}
