 ///
 /// @file    Configuration.cc
 /// @author  liweihang
 /// @date    2018-05-27 01:49:02
 ///

#include "Configuration.h"
#include <iostream>
#include <sstream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::string;
using std::map;

namespace lwh
{	
	Configuration * Configuration::pInstance_ = getInstance();

	Configuration* Configuration::getInstance()
	{
		if(NULL == pInstance_)
		{
			pInstance_ = new Configuration;
		}
		return pInstance_;
	}
	
	map<string,string> & Configuration::getConfigMap()
	{
		return _configMap;
	}

	bool Configuration::init(const string & filepath)
	{
		ifstream ifs(filepath);
		if(!ifs)
		{
			cout << "file open error" << endl;
			return false;
		}

		string line;
		while(getline(ifs,line))
		{
			stringstream iss(line);
			string key,value;
			iss >> key >> value;
			_configMap.insert(make_pair(key,value));
		}

		ifs.close();
		return true;
	}

	void Configuration::show()
	{
		for(auto num:_configMap)
		{
			cout << num.first << "----->" << num.second << endl;
		}
	}
}
