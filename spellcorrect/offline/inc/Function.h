///
/// @file    Function.h
/// @author  liweihang
/// @date    2018-05-27 01:20:47
///

#ifndef __LWH_FUNCTION_H
#define __LWH_FUNCTION_H
#include <iostream>
#include <string>
using std::cout;
using std::endl;
namespace lwh
{
	inline void transform(std::string &word)
	{
		size_t idx;
		for(idx = 0;idx < word.size();++idx)
		{
			if(word[idx] < 97)
			{
				word[idx] = word[idx] + 32;
			}
		}
	}
}
#endif
