///
/// @file    DictProducer.cc
/// @author  liweihang
/// @date    2018-05-26 17:23:28
///

#include "./include/cppjieba/Jieba.hpp"
#include "../inc/Function.h"
#include "../inc/DictProducer.h"
#include <unistd.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::cout;
using std::istringstream;
using std::endl;


const char* const DICT_PATH = "../src/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../src/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../src/dict/user.dict.utf8";
const char* const IDF_PATH = "../src/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../src/dict/stop_words.utf8";

namespace lwh
{
	DictProducer::DictProducer(const std::string & dir)
	:dir_(dir)
	{
		cout << "DictProducer" << dir_ << endl;
		files_.push_back(dir_);
	}

	void DictProducer::build_dict()
	{	
		ifstream ifs(dir_);
		if(!ifs)
		{
			cout << "read file error" << endl;
			exit(-1);
		}
		std::string text;
		while(getline(ifs,text))
		{
			istringstream  line(text);	
			std::string word;
			while(line >> word)
			{
				if((word[0] > 64 && word[0] < 91)||(word[0] > 96 && word[0] < 123))
				{
					transform(word);
					dict_[word] ++;
				}
			}
		}
		ifs.close();
	}

	void DictProducer::build_cn_dict()
	{	
		std::ofstream ofs("../cndict.data");
		ifstream ifs("../yuliao/cn_file");
		if(!ifs)
		{
			cout << "Read File Error" << endl;
			exit(-1);
		}
		
		cppjieba::Jieba jieba(
					DICT_PATH,
					HMM_PATH,
					USER_DICT_PATH,
					IDF_PATH,
					STOP_WORD_PATH
							);
		std::vector<std::string> words;
		std::map<std::string,int> mapdict;
		std::string line;
		while(ifs >> line)
		{
			jieba.Cut(line,words,true);
			for(size_t idx = 0;idx < words.size();++idx)
			{
				mapdict[words[idx]] ++;
			}
		}

		for(auto num:mapdict)
		{
			ofs << num.first << "\t" << num.second << endl;
		}
	}

	void DictProducer::store_dict(const char * filepath)
	{	
		std::ofstream ofs(filepath);
		for(auto num: dict_)
		{
			ofs << num.first << " " << num.second << endl;			
		}
		ofs.close();
	}

	void DictProducer::show_files() const
	{
		char buf[1024];
		::memset(buf,0,sizeof(buf));
	}

	void DictProducer::show_dict() const
	{
		for(auto num: dict_)
		{
			cout << num.first << endl;
		}
	}

	void DictProducer::get_files()
	{
		
	}

	void DictProducer::push_dict(const std::string & word)
	{
		dict_[word]++;	  
	}
}
