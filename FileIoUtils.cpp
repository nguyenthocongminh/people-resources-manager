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
#include <cstring>

#include "Employee.h"
#include "FileIoUtils.h"
#include "ValidateUtils.h"

using namespace std;

string FileIoUtils::_resourceFile = "./employees.txt";
string FileIoUtils::_sizeOfResourceFile = "./employees-size.txt";

list<Employee *> FileIoUtils::_employees;

const list<Employee *> FileIoUtils::listEmployee()
{
    return FileIoUtils::_employees;
};

bool FileIoUtils::addEmployee(Employee *employee){
    ofstream fstream_ob;
    fstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::app);
    fstream_ob << employee->id() << ","
               << employee->name() << ","
               << employee->dateOfBirth() << ","
               << employee->address() << ","
               << employee->department() << endl;
    fstream_ob.close();

    FileIoUtils::increaseSizeResource();
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

int FileIoUtils::increaseSizeResource()
{

    int size = FileIoUtils::getSizeofResource();
    size += 1;

    ofstream fstream_ob;
    fstream_ob.open(FileIoUtils::_sizeOfResourceFile.c_str(), ios::trunc);
    fstream_ob << size;
    fstream_ob.close();

    return size;
}

int FileIoUtils::getSizeofResource()
{
    int size = 0;
    ifstream ifstream_size;
    ifstream_size.open(FileIoUtils::_sizeOfResourceFile.c_str(), ios::in);
    if(!ifstream_size.is_open()){
        return 0;
    }

    ifstream_size >> size;
    return size;
}

void FileIoUtils::readDataFormCSV(const string &filePath, bool printResult) {
    string row[5];

    ifstream ifstream_ob;
    ifstream_ob.open(filePath, ios::in);
    if (ifstream_ob.is_open()) {
        string line, word;
        while (ifstream_ob >> line) {
            stringstream s(line);
            int i=0;
            while (getline(s, word, ',')) {
                row[i++] = word;
            }
            Employee *em = new Employee(row[0], row[1], row[2], row[3], row[4]);
            list<string> validate = ValidateUtils::validateEmployee(*em);
            if(validate.empty()){
                FileIoUtils::addEmployee(em);
                if (printResult) {
                    cout << "\n*******\n";
                    cout << row[0] << ": Success";
                    cout << "\n*******\n";
                }
            } else {
                if (printResult) {
                    ValidateUtils::printValid(validate);
                }
            }
        }
    } else {
        cout << "\n*******\n";
        cout << "Error: " << strerror(errno);
        cout << "\n*******\n\n";
    }
    ifstream_ob.close();
}

void FileIoUtils::refeshData()
{
    FileIoUtils::_employees.clear();

    string row[5];

    ifstream ifstream_ob;
    ifstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::in);
    string line, word;
    while (getline(ifstream_ob, line)) {
        stringstream s(line);
        int i=0;
        while (getline(s, word, ',')) {
            row[i++] = word;
        }
        Employee *em = new Employee(row[0], row[1], row[2], row[3], row[4]);
        FileIoUtils::_employees.push_back(em);
    }
    ifstream_ob.close();
}
