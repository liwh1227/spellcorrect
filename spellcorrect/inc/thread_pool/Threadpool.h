 
#ifndef __LWH_THREADPOOL_H__
#define __LWH_THREADPOOL_H__

#include "TaskQueue.h"
#include <functional>
#include <vector>
#include <memory>

using std::shared_ptr;
using std::vector;
namespace lwh
{

typedef std::function<void()> Task;
class Thread;
class Threadpool
{
public:
	Threadpool(size_t threadNum = 4, size_t taskSize = 10);

	void start();
	void stop();
	void addTask(Task && ptask);
private:
	Task getTask();
	void threadFunc();//每一个线程都要做的事

private:
	size_t _threadNum;
	size_t _taskSize;
	TaskQueue _taskQue;
	vector<shared_ptr<Thread>> _threads;
	bool _isExit;
};

}//en of namespace lwh

#endif
