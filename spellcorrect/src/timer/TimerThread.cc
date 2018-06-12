 ///
 /// @file    TimerThread.cc
 /// @author  liweihang
 /// @date    2018-05-31 06:18:54
 ///
 
#include "TimerThread.h"

TimerThread::TimerThread(TimerThreadCallback cb,
						int init_sec,
						int interval_sec)
	:_timer(cb,init_sec,interval_sec)
	,_thread(std::bind(&Timer::start,&_timer)) 
	{}

void TimerThread::start()
{
	_thread.start();
}

void TimerThread::stop()
{
	_timer.stop();
}
