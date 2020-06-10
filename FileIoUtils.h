//
//  FileIoUtils.h
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#ifndef FileIoUtils_hpp
#define FileIoUtils_hpp

#include <stdio.h>
#include <list>
#include <string>
using namespace std;

class Employee;

class FileIoUtils {
    
private:
    static string _resourceFile;
    
public:
    static bool addEmployee(Employee *employee);
    static void loadAllEmployee(list<Employee> & employees);
    static list<Employee> & readEmployeeFromCsv(string & path);
    static bool checkExist(string & path);
};

#endif /* FileIoUtils_hpp */
