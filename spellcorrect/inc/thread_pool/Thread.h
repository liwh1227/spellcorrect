 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-11-24 09:58:36
 ///
 
#ifndef __LWH_THREAD_H__
#define __LWH_THREAD_H__

#include "Noncopyable.h"
#include <pthread.h>
#include <string>
#include <sstream>
#include <functional>

using std::string;

namespace lwh
{

inline string int2str(int number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

namespace current_thread
{
extern __thread const char * threadName;
}

class Thread
: Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback && cb,const string & name = string());
	~Thread();

	void start();
	void join();
	pthread_t getpthId() const;
	bool isRunning() const;
	static void * threadFunc(void * arg);
	
private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
	string _name;
};

}//end of namespace lwh

#endif
