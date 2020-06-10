//
//  CheckPoint.cpp
//  people-resource
//
//  Created by Trieu on 6/11/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include "CheckPoint.h"
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

CheckPoint::CheckPoint(const string &employeeId, const string &date, const string &value)
: _employeeId(employeeId), _date(date), _value(value)
{
    
}

const string & CheckPoint::employeeId() const
{
    return _employeeId;
}

const string & CheckPoint::date() const
{
    return _date;
}
const string & CheckPoint::value() const
{
    return _value;
}

void CheckPoint::printInfo() const
{
    cout << _employeeId << " - " << _date << " - " << value() << endl;
}
