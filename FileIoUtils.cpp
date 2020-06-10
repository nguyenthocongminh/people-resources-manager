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
#include<fstream>
#include <sstream>

#include "Employee.h"
#include "FileIoUtils.h"

using namespace std;

string FileIoUtils::_resourceFile = "./employees.txt";

bool FileIoUtils::addEmployee(Employee *employee){
    
    ofstream fstream_ob;
    fstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::app);
    fstream_ob << employee->id() << ","
               << employee->name() << ","
               << employee->dateOfBirth() << ","
               << employee->address() << ","
               << employee->department() << endl;
    fstream_ob.close();
    return true;
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

bool FileIoUtils::checkExist(string &path)
{
    ifstream f(path.c_str());
    return f.good();
}
