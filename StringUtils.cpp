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

