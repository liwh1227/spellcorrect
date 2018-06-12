 ///
 /// @file    Condition.h
 ///
 
#ifndef __LWH_CONDITION_H__
#define __LWH_CONDITION_H__

//#include "MutexLock.h"  --> 放在Condition.cc的实现之中去,不要放在这里

#include <pthread.h>
namespace lwh
{

class MutexLock;//类的前向声明
class Condition
{
public:
	Condition(MutexLock & mutex);
	~Condition();

	void wait();
	void notify();
	void notifyAll();
private:
	pthread_cond_t _cond;
	MutexLock & _mutex;//Condition与MutexLock是单向的关联关系:Condition知道MutexLock的存在，但MutexLock并不知道Condition的存在
};

}// end of namespace lwh

#endif
