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

#include "Employee.h"
#include "FileIoUtils.h"

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
    fstream_ob.write( (char *) employee, sizeof(*employee));
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
    
//    FILE  *file;
//    file = fopen(FileIoUtils::_sizeOfResourceFile.c_str(),"w+");
//    fprintf(file, "%d", size);
//    fclose(file);
    
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

void FileIoUtils::refeshData()
{
    
    int size = FileIoUtils::getSizeofResource();
    if(size == 0){
        return;
    }
    Employee employees[size];
    
    ifstream ifstream_ob;
    ifstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::in);
    ifstream_ob.read( (char *) & employees, sizeof(employees));
    
    FileIoUtils::_employees.clear();
    for(int i = 0; i < size; i++)
    {
        static Employee e = employees[i];
        FileIoUtils::_employees.push_back(&e);
    }
    ifstream_ob.close();
}
