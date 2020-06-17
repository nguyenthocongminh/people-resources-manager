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
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>

#include "Employee.h"
#include "FileIoUtils.h"
#include "CheckPoint.h"
#include "EmployeeDTO.h"
#include "DateUtils.h"
using namespace std;

string FileIoUtils::_resourceFile = "employees.txt";

void FileIoUtils::addEmployee(Employee *employee){
    
    ofstream fstream_ob;
    fstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::app);
    fstream_ob << employee->id() << ","
               << employee->name() << ","
               << employee->dateOfBirth() << ","
               << employee->address() << ","
               << employee->department() << endl;
    fstream_ob.close();
}

void FileIoUtils::addListEmployees(list<Employee> &employees)
{
    
    ofstream fstream_ob;
    fstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::app);
    list<Employee>::const_iterator it;
    for (it = employees.begin(); it != employees.end(); it++) {
        fstream_ob
        << it->id() << ","
        << it->name() << ","
        << it->dateOfBirth() << ","
        << it->address() << ","
        << it->department()
        << endl;
    }

    fstream_ob.close();
}

void FileIoUtils::loadAllEmployee(list<Employee> & employees)
{
    string row[5];
    ifstream ifstream_ob;
    ifstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::in);
    string line, word;
    
    while (getline(ifstream_ob, line)) {
        stringstream s(line);
        int i = 0;
        while (getline(s, word, ',')) {
            row[i++] = word;
        }
        Employee *em = new Employee(row[0], row[1], row[2], row[3], row[4]);
        employees.push_back(*em);
    }
    ifstream_ob.close();
}

list<Employee> & FileIoUtils::readEmployeeFromCsv(string &path)
{

    ifstream fin;
    fin.open(path, ios::in);

    static list<Employee> result;
    result.clear();

    if(!fin.is_open()) {
        return result;
    }
    
    string line, word;
    
    while (getline(fin, line)) {
        stringstream s(line);
        int i = 0;
        string row[5];
        while (getline(s, word, ',')) {
            
            row[i++] = word;
        }
        Employee *em = new Employee(row[0], row[1], row[2], row[3], row[4]);
        result.push_back(*em);
    }
    result.pop_front();
    fin.close();
    return result;
}

void FileIoUtils::addCheckPoint(const CheckPoint & checkpoint)
{
    string fileName = FileIoUtils::genCheckpointFileName(checkpoint.employeeId());
    ofstream fout;
    fout.open(fileName, ios::app);
    if (fout.is_open()) {
        fout << checkpoint.date() << "," << checkpoint.value() << endl;
    }
    fout.close();
}
list<CheckPoint> FileIoUtils::loadCheckPoint(const string & employeeId)
{
    list<CheckPoint> checkpoints;
    
    string fileName = FileIoUtils::genCheckpointFileName(employeeId);
    ifstream fin;
    fin.open(fileName, ios::in);
    if (fin.is_open()) {
        string line, word;

        while (getline(fin, line)) {
            stringstream s(line);
            int i = 0;
            string row[2];
            while (getline(s, word, ',')) {
                row[i++] = word;
            }
            CheckPoint *cp = new CheckPoint(employeeId, row[0], row[1]);
            checkpoints.push_back(*cp);
        }
    }
    fin.close();
    
    return checkpoints;
}

const string FileIoUtils::genCheckpointFileName(const string & employeeId)
{
    
    string fileName = "checkpoint-" + employeeId + ".csv";
    return fileName;
}

const string FileIoUtils::genCheckpointHistoryMulti(const vector<list<EmployeeDTO>> &employeesVector, int month, int year)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string fileName = "checkpoint-history-"+ to_string(month) + "-" + to_string(year) + "__" + to_string(ltm->tm_year + 1900) + "_" + to_string(1 + ltm->tm_mon) + "_" + to_string(ltm->tm_mday) + to_string(ltm->tm_hour) + "_" + to_string(ltm->tm_min) + "_" + to_string(ltm->tm_sec) + ".csv";
    
    ofstream fstream_ob;
    fstream_ob.open(fileName, ios::app);
    
    // header
    fstream_ob << "ID," << "Ten," << "Phong";
    
    int numberOfDays = DateUtils::getNumberOfDays(month, year);
    string dayOfMonth[numberOfDays];
    
    string monthStr = month >= 10 ? to_string(month) : "0" + to_string(month);
    
    for(int i = 1; i <= numberOfDays; i++){
        string dayStr = i >= 10 ? to_string(i) : "0" + to_string(i);
        string dateStr = dayStr + "/" + monthStr + "/" + to_string(year);
        dayOfMonth[i-1] = dateStr;
        fstream_ob << "," << dateStr;
    }
    fstream_ob << endl;
    // end header
    
    list<CheckPoint>::const_iterator itcp;
    list<EmployeeDTO>::const_iterator itemDto;
    
    for(list<EmployeeDTO> employees : employeesVector) {
        for (itemDto = employees.begin(); itemDto != employees.end(); itemDto++) {
            fstream_ob << itemDto->id() << "," << itemDto->name() << "," << itemDto->department();
            for(int i = 0; i < numberOfDays; i++){
                string status = "-1xozoOo";
                
                for (itcp = itemDto->checkpoints().begin(); itcp != itemDto->checkpoints().end(); itcp++) {
                    if(dayOfMonth[i].compare(itcp->date()) == 0) {
                        fstream_ob << "," << itcp->value();
                        status = itcp->value();
                        break;
                    }
                }
                if(status == "-1xozoOo"){
                    fstream_ob << "," << "X";
                }
                
            }
            fstream_ob << endl;
        }
    }
    
    
    return fileName;
}


const string FileIoUtils::genCheckpointHistory(const list<EmployeeDTO> &employees, int month, int year)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    string fileName = "checkpoint-history-"+ to_string(month) + "-" + to_string(year) + "__" + to_string(ltm->tm_year + 1900) + "_" + to_string(1 + ltm->tm_mon) + "_" + to_string(ltm->tm_mday) + to_string(ltm->tm_hour) + "_" + to_string(ltm->tm_min) + "_" + to_string(ltm->tm_sec) + ".csv";
    
    ofstream fstream_ob;
    fstream_ob.open(fileName, ios::app);
    
    // header
    fstream_ob << "ID," << "Ten," << "Phong";
    
    int numberOfDays = DateUtils::getNumberOfDays(month, year);
    string dayOfMonth[numberOfDays];
    
    string monthStr = month >= 10 ? to_string(month) : "0" + to_string(month);
    
    for(int i = 1; i <= numberOfDays; i++){
        string dayStr = i >= 10 ? to_string(i) : "0" + to_string(i);
        string dateStr = dayStr + "/" + monthStr + "/" + to_string(year);
        dayOfMonth[i-1] = dateStr;
        fstream_ob << "," << dateStr;
    }
    fstream_ob << endl;
    // end header
    
    list<CheckPoint>::const_iterator itcp;
    list<EmployeeDTO>::const_iterator itemDto;
    
    for (itemDto = employees.begin(); itemDto != employees.end(); itemDto++) {
        fstream_ob << itemDto->id() << "," << itemDto->name() << "," << itemDto->department();
        for(int i = 0; i < numberOfDays; i++){
            string status = "-1xozoOo";
            
            for (itcp = itemDto->checkpoints().begin(); itcp != itemDto->checkpoints().end(); itcp++) {
                if(dayOfMonth[i].compare(itcp->date()) == 0) {
                    fstream_ob << "," << itcp->value();
                    status = itcp->value();
                    break;
                }
            }
            if(status == "-1xozoOo"){
                fstream_ob << "," << "X";
            }
            
        }
        fstream_ob << endl;
    }

    
    return fileName; // Have to replace return absulute file path
}

bool FileIoUtils::checkExist(string &path)
{
    ifstream f(path.c_str());
    return f.good();
}

void FileIoUtils::rewriteCheckPoint(string & employeeId, list<CheckPoint> & checkPoints)
{
    string fileName = FileIoUtils::genCheckpointFileName(employeeId);
    ofstream fstream_ob;
    fstream_ob.open(fileName, ios::trunc);

    if (fstream_ob.is_open()) {
        list<CheckPoint>::const_iterator itcp;
        for (itcp = checkPoints.begin(); itcp != checkPoints.end(); itcp++) {
            fstream_ob << itcp->date() << "," << itcp->value() << endl;
        }
    }
    fstream_ob.close();
}
