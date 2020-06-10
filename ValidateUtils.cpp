//
//  ValidateUtils.cpp
//  people-resource
//
//  Created by Trieu on 6/5/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include "ValidateUtils.h"
#include "FileIoUtils.h"
#include "Employee.h"
#include <string>
#include <sstream>
#include <regex>
#include <iostream>
#include <ctime>
#include "EmployeeManager.h"

using namespace std;

const list<string> ValidateUtils::validateEmployee(const Employee &em, const list<Employee> & currentEms)
{
    list<string> validate;
    
    if (!em.id().empty()) {
        list<Employee>::const_iterator it;
        for (it = currentEms.begin(); it != currentEms.end(); it++) {
            if (it->id() == em.id()) {
                string errorId = "Trung id : " + em.id();
                validate.push_back(errorId);
            }
        }
    } else {
        string errorId = "ID khong duoc de trong";
        validate.push_back(errorId);
    }
    
    if (em.name().empty()) {
        string errorName = "Ten khong duoc de trong";
        validate.push_back(errorName);
    }
    
    if(!validateDate(em.dateOfBirth())) {
        string errorDateOfBirth = "Ngay sinh khong dung dd/MM/yyyy";
        validate.push_back(errorDateOfBirth);
    }
    
    if(em.address().empty()) {
        string errorAddress = "Dia chi khong duoc de trong";
        validate.push_back(errorAddress);
    }
    if(em.department().empty()) {
        string errorDepartment = "Phong ban khong duoc de trong";
        validate.push_back(errorDepartment);
    }
    
    return validate;
}

void ValidateUtils::printValid(list<string> & valid)
{
    cout << "\n*******\n";
    for(auto const& i : valid)
    {
        cout << i << "\n";
    }
    cout << "\n*******\n";
}

void ValidateUtils::print(list<string> & listStr)
{

    for(auto const& i : listStr)
    {
        cout << i << "\n";
    }
}

bool ValidateUtils::validateDate(const string &date) {
    stringstream s(date);
    string list[3];
    string tmp;
    int i = 0;
    while (getline(s, tmp, '/') && i < 3) {
        list[i++] = tmp;
    }
    int day, month, year;
    istringstream(list[0]) >> day;
    istringstream(list[1]) >> month;
    istringstream(list[2]) >> year;

    if (day < 1 || day > 31 || month < 1 || month > 12) {
        return false;
    }
    if ((month==4 || month==6 || month==9|| month==11) && day == 31) {
        return false;
    }
    if (month == 2 && (day > 29 || (day == 29 && !(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))))) {
        return false;
    }
    time_t t = time(0);
    struct tm * timeStruct = localtime(&t);
    if (year < 1900 || (year > timeStruct->tm_year)) {
        return false;
    }
    if (year == timeStruct->tm_year) {
        if (month > (timeStruct->tm_mon + 1) || (month == (timeStruct->tm_mon + 1) && day > (timeStruct->tm_mday))) {
            return false;
        }
    }
    return true;
}
