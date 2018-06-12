 ///
 /// @file    CacheManager.h
 /// @author  liweihang
 /// @date    2018-05-29 17:34:01
 ///

#ifndef __CACHEMANAGER_H
#define __CACHEMANAGER_H
#include "Cache.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class CacheManager
{
public:
    static	void initCache(size_t sz,const string & filename);
	static Cache & getCache(pthread_t pthId);
	static void updateCache();
private:	
	static vector<Cache> _cachesList;
};
#endif
