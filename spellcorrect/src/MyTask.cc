 ///
 /// @file    MyTask.cc
 /// @author  liweihang
 /// @date    2018-05-27 21:24:23

#include "../inc/cache/Cache.h"
#include "../inc/cache/CacheManager.h"
#include "../inc/MyTask.h"
#include "../inc/MyDict.h"
#include "../inc/EditDistance.h"
#include "../inc/thread_pool/Thread.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <pthread.h>

using std::cout;
using std::endl;

namespace lwh
{
	MyTask::MyTask(const string & queryWord,const TcpConnectionPtr & conn)
	:_queryWord(queryWord)
	,_conn(conn)
	{}
	
	void MyTask::execute()
	{	
		Cache &cache = CacheManager::getCache(atoi(lwh::current_thread::threadName));
		cout << "要查询的词是:" << _queryWord << endl;
		string result = cache.query(_queryWord);
		
		if(result != string())
		{
			_conn->sendInLoop(result);
			cout << "> response client" << endl;
			return;
		}
		queryIndexTable();
		response();
	}

	void MyTask::queryIndexTable()
	{	
		//获取索引表 map<string,set<int>>
		auto indexTable = MyDict::createInstance()->get_index_table();
		string ch;
		for(size_t idx = 0;idx != _queryWord.size();)
		{	
			size_t nBytes = nBytesCode(_queryWord[idx]);
			ch = _queryWord.substr(idx,nBytes);
			idx += nBytes;
			if(indexTable.count(ch))
			{
				cout << "the indexTable has this character" << ch << endl;
				statistic(indexTable[ch]);
			}
		}
	}
	
	void MyTask::response()
	{
		if(_resultQue.empty())
		{
			string result = "no answer!";
			_conn->sendInLoop(result);
		}else
		{	
			MyResult result = _resultQue.top();
			_conn->sendInLoop(result._word);
			Cache & cache = CacheManager::getCache(atoi(lwh::current_thread::threadName));
			cache.addElement(_queryWord,result._word);
			cout << ">add Element into cache success!" << endl;
		}
		cout << ">response client" << endl;
	}

	void MyTask::statistic(set<int> &iset)
	{
		auto dict = MyDict::createInstance()->get_dict();
		auto iter =	iset.begin();
		for(;iter != iset.end(); ++iter)
		{
			string rhsWord = dict[*iter].first;
			int idist = distance(rhsWord);
			if(idist < 3)
			{
				MyResult res;
				res._word = rhsWord;
				res._iFreq = dict[*iter].second;
				res._iDist = idist;
				_resultQue.push(res);
			}
		}	
	}

	int MyTask::distance(const string & rhsWord)
	{
		return editDistance(_queryWord,rhsWord);
	}
}
