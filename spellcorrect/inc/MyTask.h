 ///
 /// @file    MyTask.h
 /// @author  liweihang
 /// @date    2018-05-27 20:22:32
 ///

#ifndef __LWH_MYTASK_H
#define __LWH_MYTASK_H
#include "../Reactor/TcpConnection.h"
#include "../inc/cache/Cache.h"
#include <string>
#include <vector>
#include <queue>
#include <set>

using std::string;
using std::priority_queue;
using std::vector;
using std::set;

namespace lwh
{
struct MyResult
{
	string _word;
	int _iFreq;
	int _iDist;
};
//优先级队列中的比较
struct MyCompare
{
	bool operator()(const MyResult & lhs,const MyResult & rhs)
	{
		if(lhs._iDist > rhs._iDist)
		{
			return true;
		}else if(lhs._iDist == rhs._iDist &&
				 lhs._iFreq < rhs._iFreq )
		{
			return true;
		}else if(lhs._iDist == rhs._iDist &&
				 lhs._iFreq == rhs._iFreq &&
				 lhs._word > rhs._word)
		{
			return true;
		}
		else
			return false;
	}
};
class MyTask
{
public:
	MyTask(const string & queryWord,const TcpConnectionPtr & conn);
	void execute();//执行cache，暂时不用
private:
	void queryIndexTable();
	void statistic(set<int> & iset);
	int distance(const string & rhs);
	void response();
private:
	string _queryWord;
	TcpConnectionPtr _conn;
	priority_queue<MyResult,vector<MyResult>,MyCompare> _resultQue;
};
}
#endif
