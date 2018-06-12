 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-11-24 10:01:09
 ///
 
#include "Thread.h"
#include <iostream>

namespace lwh
{
namespace current_thread
{
	__thread const char * threadName = "lwh";//* threadName不能被修改
	//threadName可以修改
} 

struct ThreadData
{
	typedef lwh::Thread::ThreadCallback ThreadCallback;
	ThreadCallback _cb;
	string _name;

	ThreadData(const ThreadCallback & cb,const string & name)
	:_cb(cb)
	,_name(name) 
	{}

	void runInThread()
	{
		current_thread::threadName = _name.empty()? "lwh":_name.c_str();
		if(_cb)
			_cb();
	}
};

Thread::Thread(ThreadCallback && cb,const string & name)
: _pthId(0)
, _isRunning(false)
, _cb(std::move(cb))
,_name(name)	
{}

void Thread::start()
{	
	ThreadData * pdata = new ThreadData(_cb,_name);
	pthread_create(&_pthId, NULL,threadFunc,pdata);	
	_isRunning = true;
}

pthread_t Thread::getpthId() const
{
	return _pthId;
}

void * Thread::threadFunc(void * arg)
{
	ThreadData * pdata = static_cast<ThreadData*>(arg);
	if(pdata)
		pdata -> runInThread();
	delete  pdata;
	return NULL;
}

void Thread::join()
{
	if(_isRunning)
	{
		pthread_join(_pthId, NULL);
		_isRunning = false;
	}
}

bool Thread::isRunning() const
{
	return _isRunning;
}

Thread::~Thread()
{
	if(_isRunning)
	{
		pthread_detach(_pthId);
		_isRunning = false;
	}
}

}
