//
//  EmployeeManager.hpp
//  people-resource
//
//  Created by Trieu on 6/4/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#ifndef EmployeeManager_hpp
#define EmployeeManager_hpp
#include <stdio.h>
#include <string>
using namespace std;

class Employee;

class EmployeeManager
{
private:
    static EmployeeManager *_instance;
    
private:
    EmployeeManager();
    
public:
    static EmployeeManager *instance();
    
    void insertEmployee();
    void findEmployeeById();
    void printEmployees();
    void printEmployee(Employee employee);
    void importDataEmployeeCSV();
};

#endif /* EmployeeManager_hpp */
