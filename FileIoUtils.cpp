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

bool FileIoUtils::addEmployee(Employee *employee){
    
    ofstream fstream_ob;
    fstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::app);
    fstream_ob.write( (char *) employee, sizeof(*employee));
    fstream_ob.close();
    
    FileIoUtils::increaseSizeResource();
    return true;
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

void FileIoUtils::loadAllEmployee(list<Employee> & employees)
{
    int size = FileIoUtils::getSizeofResource();
    if(size == 0){
        return;
    }
    Employee ems[size];
    
    ifstream ifstream_ob;
    ifstream_ob.open(FileIoUtils::_resourceFile.c_str(), ios::in);
    ifstream_ob.read( (char *) & ems, sizeof(ems));
    ifstream_ob.close();
    
    for(int i = 0; i < size; i++)
    {
        Employee *em = new Employee(ems[i].id(), ems[i].name(), ems[i].dateOfBirth(), ems[i].address(), ems[i].department());
        employees.push_back(*em);
    }
}
