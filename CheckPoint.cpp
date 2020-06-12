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

bool CheckPoint::operator <(const CheckPoint & _checkpoint) const {
    stringstream _s(_checkpoint.date()), s(_date);
    string _list[3], list[3];
    string _tmp, tmp;
    int i = 0;
    while (getline(_s, _tmp, '/') && i < 3) {
        _list[i++] = _tmp;
    }
    int _day, _month, _year;
    istringstream(_list[0]) >> _day;
    istringstream(_list[1]) >> _month;
    istringstream(_list[2]) >> _year;

    i = 0;
    while (getline(s, tmp, '/') && i < 3) {
        list[i++] = tmp;
    }
    int day, month, year;
    istringstream(list[0]) >> day;
    istringstream(list[1]) >> month;
    istringstream(list[2]) >> year;

    if (year > _year) {
        return false;
    }
    if (year == _year) {
        if (month > _month) {
            return false;
        }
        if (month == _month) {
            if (day > _day || day == _day) {
                return false;
            }
        }
    }
    return true;
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
void CheckPoint::printValue() const
{
    cout << _date << " - " << value() << endl;
}
