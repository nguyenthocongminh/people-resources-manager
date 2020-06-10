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
#include <list>
using namespace std;

class Employee;

class EmployeeManager
{
private:
    static EmployeeManager *_instance;
    
private:
    EmployeeManager();
    
private:
    list<Employee> _employees;
    
public:
    static EmployeeManager *instance();
    
    void insertEmployee();
    void findEmployeeById();
    void printEmployees();
    void refeshData();
    void importCsv();
    void addCheckPoint();
};

#endif /* EmployeeManager_hpp */
