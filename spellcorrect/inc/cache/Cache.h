 ///
 /// @file    MyCache.cc
 /// @author  liweihang
 /// @date    2018-05-29 16:32:49
 ///

#ifndef __MY_CACHE_H
#define __MY_CACHE_H
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

using std::unordered_map;
using std::string;
using std::list;
using std::pair;

class Cache
{
public:
	typedef pair<string,string> key_value_pair_t;
	typedef list<pair<string,string>>::iterator list_iterator_t;

	Cache(size_t max_size)
	:_max_size(max_size)
	{}

	void readFromFile(const string & filename);
	void writeToFile(const string & filename);
	void update(const Cache & rhs);
	void addElement(const string &key,const string &value);
	string query(const string & word);
	void debug();

private:
	size_t _max_size;
	list<key_value_pair_t> _cacheList;
	unordered_map<string,list_iterator_t> _hashMap;
};
#endif
