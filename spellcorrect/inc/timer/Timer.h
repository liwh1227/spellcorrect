 ///
 /// @file    Timer.h
 /// @author  liweihang
 /// @date    2018-05-31 02:38:34
 ///

#ifndef __LWH_TIMER_H
#define __LWH_TIMER_H
#include "../thread_pool/Noncopyable.h"
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::function;

class Timer
:lwh::Noncopyable
{
public:
	typedef function<void()> TimerCallback;
	Timer(TimerCallback cb,int init_sec,int interval_sec);
	~Timer();

	void start();
	void stop();
private:
	int _fd;
	TimerCallback _cb;
	bool _isStarted;
};

#endif
