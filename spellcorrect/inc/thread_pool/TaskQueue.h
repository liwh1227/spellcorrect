 ///
 /// @file    TaskQueue.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-11-24 14:44:05
 ///
 
#ifndef __LWH_TASKQUEUE_H__
#define __LWH_TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <iostream>
#include <queue>
#include <functional>

namespace lwh
{

typedef std::function<void()> Task;
class TaskQueue
{
public:
	TaskQueue(size_t size = 10);

	void push(Task && task);
	Task pop();

	bool full() const;
	bool empty() const;

	void wakeup();

private:
	size_t _size;
	std::queue<Task> _que;
	MutexLock _mutex;
	Condition _notFull;
	Condition _notEmpty;
	bool _flag;
};

}//end of namespace lwh

#endif
