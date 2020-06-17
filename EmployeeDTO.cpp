//
//  EmployeeDTO.cpp
//  people-resource
//
//  Created by Trieu on 6/16/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include <string>
#include <list>
#include <iostream>

#include "EmployeeDTO.h"
#include "CheckPoint.h"

using namespace std;

EmployeeDTO::EmployeeDTO(const string &id,
                         const string &name,
                         const string &department,
                         const list<CheckPoint> &checkpoints)
: _id(id), _name(name), _department(department), _checkpoints(checkpoints)
{
}

const list<CheckPoint> & EmployeeDTO::checkpoints() const
{
    return _checkpoints;
}

void EmployeeDTO::printInfo() const
{
    cout << _id << "\t\t" << _name << "\t\t" << "\t\t" << _department << "\n" << endl;
}
