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

using namespace std;

const list<string> ValidateUtils::validateEmployee(Employee &em)
{
    list<string> validate;

    if (!em.id().empty()) {
        Employee *oldEm = FileIoUtils::findEmployeeById(em.id());

        if(oldEm != nullptr) {
            string errorId = "Trung id : " + em.id();
            validate.push_back(errorId);
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
    
    if(em.address().empty()){
        string errorAddress = "Dia chi khong duoc de trong";
        validate.push_back(errorAddress);
    }
    if(em.department().empty()){
        string errorDepartment = "Phong ban khong duoc de trong";
        validate.push_back(errorDepartment);
    }
    
    return validate;
}

const void ValidateUtils::printValid(list<string> & valid)
{
    cout << "\n*******\n";
    for(auto const& i : valid){
        cout << i << "\n";
    }
    cout << "\n*******\n";
}
