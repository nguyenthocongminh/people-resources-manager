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
    static list<Employee *> _employees;
    
public:
    static const list<Employee *> listEmployee();
    static bool addEmployee(Employee *employee);
    static Employee * findEmployeeById(string &id);
    
};

#endif /* FileIoUtils_hpp */
