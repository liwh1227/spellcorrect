 ///
 /// @file    TaskQueue.cc
 ///
 
#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

using namespace lwh;

TaskQueue::TaskQueue(size_t size)
: _size(size)
, _que()
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _flag(true)
{
	cout << "TaskQueue(size_t)" << endl;
}

bool TaskQueue::full() const
{
	return _que.size() == _size;
}

bool TaskQueue::empty() const
{
	return _que.size() == 0;
}


void TaskQueue::push(Task && task)
{
	MutexLockGuard mlg(_mutex);
	while(full()) //使用if是为了防止异常唤醒
	{
		_notFull.wait();
	}
	
	_que.push(task);
	_notEmpty.notify();
}

Task TaskQueue::pop()
{
	MutexLockGuard mlg(_mutex);
	while(_flag && empty())
	{
		_notEmpty.wait();
	}
	
	if(_flag)
	{
		Task task  = _que.front();
		_que.pop();

		_notFull.notify();
		return task;
	}
	else
		return NULL;
}

void TaskQueue::wakeup()
{
	_flag = false;
	_notEmpty.notifyAll();
}
