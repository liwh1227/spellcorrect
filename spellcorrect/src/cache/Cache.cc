 ///
 /// @file    Cache.cc
 /// @author  liweihang
 /// @date    2018-05-29 16:40:39
 ///

#include "../../inc/cache/Cache.h"
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;

void Cache::addElement(const string & key,const string & value)
{
	auto it = _hashMap.find(key);
	_cacheList.push_front(key_value_pair_t(key,value));

	if(it != _hashMap.end())
	{
		_cacheList.erase(it->second);
		_hashMap.erase(it);
	}

	_hashMap[key] = _cacheList.begin();
	if(_hashMap.size() > _max_size)
	{
		auto last = _cacheList.end();
		last--;
		_hashMap.erase(last->first);
		_cacheList.pop_back();
	}
}

string Cache::query(const string & word)
{	
	auto iter = _hashMap.find(word);
	if(iter != _hashMap.end())
	{	
		_cacheList.splice(_cacheList.begin(),_cacheList,iter->second);
		return iter->second->second;
	}
	else
	{	
		return string();	
	}
}

void Cache::writeToFile(const string & filename)
{
	ofstream ofs(filename);
	for(auto iter:_cacheList)
	{
		ofs << iter.first << "\t " << iter.second << endl;
	}
	
	ofs.close();
}

void Cache::readFromFile(const string & filename)
{
	ifstream ifs(filename);
	if(!ifs)
	{
		cout << "read file error!" << endl;
		exit(-1);
	}
	
	string key,value;
	while(ifs >> key >> value)
	{	
		_cacheList.push_back(key_value_pair_t(key,value));
		auto iter = _cacheList.end();
		iter--;
		_hashMap[key] = iter;
	}

	ifs.close();
}

void Cache::update(const Cache & rhs)
{	
	for(auto iter:rhs._hashMap)
	{	
		_hashMap.insert(iter);
	}
}

//展示cache文件中的内容
void Cache::debug()
{
	cout << "<-------Cache begin------->" << endl;
	for(auto elem:_hashMap)
	{
		cout << elem.first << "---->" << (elem.second)->second << endl;
	}
	cout << "<------Cache end------->" << endl;
}
