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
#include <regex>
#include <iostream>
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
    
    if(!regex_match (em.dateOfBirth(), regex("^([0-2][0-9]|(3)[0-1])(\\/)(((0)[0-9])|((1)[0-2]))(\\/)\\d{4}$"))) {
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

const void ValidateUtils::print(list<string> & listStr)
{

    for(auto const& i : listStr)
    {
        cout << i << "\n";
    }
}
