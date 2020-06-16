//
//  EmployeeDTO.cpp
//  people-resource
//
//  Created by Trieu on 6/16/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include "EmployeeDTO.h"
#include <string>
#include <list>

using namespace std;

EmployeeDTO::EmployeeDTO(const string &id,
                         const string &name,
                         const string &department,
                         const list<string> &checkpoints)
: _id(id), _name(name), _department(department), _checkpoints(checkpoints)
{
}

const list<string> & EmployeeDTO::checkpoints() const
{
    return _checkpoints;
}
