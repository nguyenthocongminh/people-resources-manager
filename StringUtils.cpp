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
#include <cctype>
#include <algorithm>

using namespace std;

bool StringUtils::containIgnoreCase(const string &str1, const string &str2)
{
    string str1_tmp, str2_tmp;
    str1_tmp = str1;
    str2_tmp = str2;
    toLower(str1_tmp);
    toLower(str2_tmp);
    return str1_tmp.find(str2_tmp) !=  string::npos;
}

void StringUtils::toLower(string &str) {
    for_each(str.begin(), str.end(), [](char & c) {
        c = tolower(c);
    });
}

void StringUtils::toUpper(string &str) {
    for_each(str.begin(), str.end(), [](char & c) {
        c = toupper(c);
    });
}
