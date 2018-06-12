///
/// @file    Mydict.cc
/// @author  liweihang
/// @date    2018-05-27 17:22:50
///

#include "../inc/MyDict.h"
#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::endl;
namespace lwh
{
	MyDict * MyDict::pInstance = NULL;

	MyDict * MyDict::createInstance()
	{
		if(NULL == pInstance)
		{
			pInstance = new MyDict;
		}
		return pInstance;
	}

	vector<std::pair<string,int>> & MyDict::get_dict()
	{
		return dict_;
	}

	map<string,set<int>> & MyDict::get_index_table()
	{
		return index_table_;
	}

	void MyDict::show_dict()
	{
		for(auto num:dict_)
		{
			std::cout << num.first << "------>" 
					  << num.second << std::endl;
		}
	}

	void MyDict::show_index_table()
	{
		for(auto num: index_table_)
		{
			cout << num.first << "---->";
			for(auto idx:num.second)
			{
				cout << idx  << " ";
			}
			cout << endl;
		}
	}
	
	//将词典内容保存到vector中
	void MyDict::read_from(const char * dictpath)
	{
		std::ifstream ifs(dictpath);
		if(!ifs)
		{
			cout << "read file error"<< endl;
			exit(-1);
		}

		string line;
		while(getline(ifs,line))
		{
			std::stringstream ss(line);
			string key;
			int value;
			ss >> key >> value;
			dict_.push_back(make_pair(key,value));
		}
		ifs.close();
	}

	void MyDict::init(const char * dictPath,const char *cndictPath)
	{
		read_from(dictPath);
		read_from(cndictPath);
		for(size_t idx = 0;idx != dict_.size();++idx)
		{
			record_to_index(idx);
		}
	}

	void MyDict::record_to_index(int idx)
	{
		string key;
		string word = dict_[idx].first;
		for(size_t iidx = 0;iidx != word.size();++iidx)
		{	
			char ch = word[iidx];
			if(ch & (1<<7))
			{//说明不是英文字符
				if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
				{
					key = word.substr(iidx,2);
					++iidx;
				}
				else if((ch & 0xF0) == 0xE0)
				{
					key = word.substr(iidx,3);
					iidx += 2;
				}
				else if((ch & 0xFF) == 0xF0 ||
						(ch & 0xFF) == 0xF1 ||
						(ch & 0xFF) == 0xF2 ||
						(ch & 0xFF) == 0xF3 ||
						(ch & 0xFF) == 0xF4 ||
						(ch & 0xFF) == 0xF5 ||
						(ch & 0xFF) == 0xF6 ||
						(ch & 0xFF) == 0xF7 
					   )
					   {
							key = word.substr(iidx,4);
							iidx += 3;
					   }
				else if((ch & 0xFF) == 0xF8 ||
						(ch & 0xFF) == 0xF9 ||
						(ch & 0xFF) == 0xFA ||
						(ch & 0xFF) == 0xFB 
						)
						{
							key = word.substr(iidx,5);
							iidx += 4;
						}
				else if((ch & 0xFF) == 0xFC||
						(ch & 0xFF) == 0xFD
					    )	
				{
					key = word.substr(iidx,6);
					iidx += 5;
				}
			}
			else
			{
				key = word.substr(iidx,1);
			}
			index_table_[key].insert(idx);
		}
	}
}
