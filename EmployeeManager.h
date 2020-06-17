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
#include <future>
#include <vector>
#include <string>
#include <list>
using namespace std;

class Employee;
class CheckPoint;
class EmployeeDTO;

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
    void searchByName();
    void checkpointHistory();
    void checkpointHistoryMultiThread();
    void readFileByThread(promise<list<EmployeeDTO>> && promise, vector<Employee> employees, int month, int year);
    
private:
    list<CheckPoint> filterByMonth(const list<CheckPoint> & checkpoints, int month, int year);
    void printCheckPointSortByDay(list<CheckPoint> & checkpoints, int month, int year);
};

#endif /* EmployeeManager_hpp */
