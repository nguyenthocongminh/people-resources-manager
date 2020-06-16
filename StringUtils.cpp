//
//  StringUtils.cpp
//  people-resource
//
//  Created by Trieu on 6/16/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#include "StringUtils.h"
#include "CheckPoint.h"
#include "DateUtils.h"

#include <string>

using namespace std;

const bool StringUtils::containIgnoreCase(const string &str1, const string &str2)
{
    // TODO: implement IgnoreCase
    return str1.find(str2) !=  string::npos;
}

list<string> StringUtils::checkpointsToListString(const int month, const int year, const list<CheckPoint> &checkpoints)
{
    list<string> result; // list string of dd/MM/yyyy: checkpoint._value
    int numberOfDays = DateUtils::getNumberOfDays(month, year);
    string dayOfMonth[numberOfDays];
    
    list<CheckPoint>::const_iterator itcp;
    
    string monthStr = month >= 10 ? to_string(month) : "0" + to_string(month);
    
    for(int i = 1; i <= numberOfDays; i++){
        string dayStr = i >= 10 ? to_string(i) : "0" + to_string(i);
        string dateStr = dayStr + "/" + monthStr + "/" + to_string(year);
        
        string text = dateStr + ": ";
        
        string status = "-1xozooo";
        for (itcp = checkpoints.begin(); itcp != checkpoints.end(); itcp++) {
            if(dateStr.compare(itcp->date()) == 0) {
                dateStr + itcp->value();
                
                status = itcp->value();
                break;
            }
        }
        if(status == "-1xozooo"){
            text + "X";
        }
        result.push_back(text);
    }
    return result;
}
