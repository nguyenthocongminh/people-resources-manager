//
//  StringUtils.hpp
//  people-resource
//
//  Created by Trieu on 6/16/20.
//  Copyright © 2020 Trieu. All rights reserved.
//

#ifndef StringUtils_h
#define StringUtils_h

#include <stdio.h>
#include <string>
#include <string>
#include <list>

using namespace std;
class CheckPoint;
class StringUtils {
    
public:
    static const bool containIgnoreCase(const string & str1, const string & str2);
    static list<string> checkpointsToListString(const int month, const int year, const list<CheckPoint> &checkpoints);
    
};
#endif /* StringUtils_h */
