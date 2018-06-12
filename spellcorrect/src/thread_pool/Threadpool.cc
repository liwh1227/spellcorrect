 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-11-24 16:27:38
 ///
 
#include "Threadpool.h"
#include "Thread.h"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;


using namespace lwh;

Threadpool::Threadpool(size_t threadNum, size_t taskSize)
: _threadNum(threadNum)
, _taskSize(taskSize)
, _taskQue(_taskSize)
, _threads()
, _isExit(false)
{
	_threads.reserve(_threadNum);
}

void Threadpool::start()
{
	for(size_t idx = 0; idx < _threadNum; ++idx)
	{
		shared_ptr<Thread> sp(new Thread(std::bind(&Threadpool::threadFunc, this),int2str(idx)));
		_threads.push_back(sp);
	}
	
	for(auto & thread : _threads)
	{	
		thread->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		
		while(!_taskQue.empty())
		{
			//::sleep(1);	
			::usleep(100);
		}
		_isExit = true;
		_taskQue.wakeup();

		for(auto & thread : _threads)
		{
			cout << "---join sub thread " << endl;
			thread->join();
		}
	}
}

void Threadpool::addTask(Task && ptask)
{
	_taskQue.push(std::move(ptask));
}

Task Threadpool::getTask()
{
	return _taskQue.pop();
}


void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task task = getTask();
		if(task)
		{
			task();
		}
	}
}
