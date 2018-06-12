///
/// @file    MyTask.h
/// @author  liweihang
/// @date    2018-05-26 01:43:05
///

#ifndef __LWH_MYTASK_H
#define __LWH_MYTASK_H
#include "TcpConnection.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace lwh
{

	class MyTask
	{
		public:
			MyTask(const string & query,const lwh::TcpConnectionPtr &conn)
			:_query(query)
			 ,_conn(conn) 
		{}

			void process()
			{
				cout <<">task is processing" << endl;
				_conn->sendInLoop(_query);
			}
		private:
			string _query;
			lwh::TcpConnectionPtr _conn;
	};

}
#endif
