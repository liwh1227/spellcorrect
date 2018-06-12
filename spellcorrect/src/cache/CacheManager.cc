///
/// @file    CacheManager.cc
/// @author  liweihang
/// @date    2018-05-29 18:00:14
///

#include "../../inc/cache/CacheManager.h"
#include "../../inc/Configuration.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

vector<Cache> CacheManager::_cachesList;

void CacheManager::initCache(size_t sz,const string & filename)
{	
	Cache cache(10);
	//将所有的cache进行更新
	cache.readFromFile(filename);
	for(size_t idx = 0;idx != sz;++idx)
		_cachesList.push_back(cache);
}

Cache & CacheManager::getCache(size_t idx)
{	
	return _cachesList[idx];
}

//不同cache相互更新
void CacheManager::updateCache()
{
	cout << ">Starting update Caches!" << endl;
	auto it1 = _cachesList.begin();
	auto it2 = ++it1;
	//把其他线程中的cache都添加到当前线程中的cache中
	for(; it2 != _cachesList.end();++it2)
	{
		it1->update(*it2);
	}

	it1 = _cachesList.begin();
	it2 = ++it1;
	for(;it2 != _cachesList.end();++it2)
	{
		it2->update(*it1);
	}

	//更新完后，只需将一个更新好的caches回写会磁盘即可
	//这样也避免了不必要的临界资源问题
	it1->writeToFile(lwh::Configuration::getInstance()->getConfigMap()["cache"]);
	cout << ">Update Success" << endl;
}

