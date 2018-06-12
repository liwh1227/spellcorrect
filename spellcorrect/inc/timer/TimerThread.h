 /// @file    TimerThread.cc
 /// @author  liweihang
 /// @date    2018-05-31 06:07:12

#ifndef __LWH_TIMERTHREAD_H
#define __LWH_TIMERTHREAD_H
#include "Timer.h"
#include "../thread_pool/Thread.h"
#include <functional>

class TimerThread
{
public:
	typedef std::function<void()> TimerThreadCallback;
	TimerThread(TimerThreadCallback cb,int init_sec,int interval_sec);

	void start();
	void stop();
private:
	Timer _timer;
	lwh::Thread _thread;
};

#endif
