//
//  ValidateUtils.hpp
//  people-resource
//
//  Created by Trieu on 6/5/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#ifndef ValidateUtils_hpp
#define ValidateUtils_hpp

#include <stdio.h>
#include <string>
#include <list>

using namespace std;

class Employee;

class ValidateUtils
{
public:
    static const list<string> validateEmployee(Employee &em, const list<Employee> & currentEms);
    static const void printValid(list<string> & valid);
};
#endif /* ValidateUtils_hpp */
