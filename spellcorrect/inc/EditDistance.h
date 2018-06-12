 ///
 /// @file    EditDistance.h
 /// @author  liweihang
 /// @date    2018-05-28 17:21:01
 ///

#ifndef __LWH_EDITDISTANCE_H
#define __LWH_EDITDISTANCE_H
#include <iostream>
#include <string>
size_t nBytesCode(const char ch);
size_t length(const std::string &str);
int tripleMin(const int &a,const int &b,const int &c);
int editDistance(const std::string &lhs,const std::string &rhs);

#endif
