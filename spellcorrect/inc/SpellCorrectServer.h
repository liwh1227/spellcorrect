 ///
 /// @file    SpellCorrectServer.h
 /// @author  liweihang
 /// @date    2018-05-28 17:58:29
 ///

#ifndef __LWH_SPELLCORRECTSERVER_H
#define __LWH_SPELLCORRECTSERVER_H
#include "../Reactor/TcpServer.h"
#include "../inc/cache/CacheManager.h"
#include "../thread_pool/Threadpool.h"
#include "../timer/TimerThread.h"

#include <string>
using std::string;

namespace lwh
{
class SpellcorrectServer
{
public:
	SpellcorrectServer();
	void start();
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn);
	void onClose(const TcpConnectionPtr& conn);
private:
	TcpServer _tcpServer;
	Threadpool _threadpool;
	TimerThread _timer;

};
}
#endif
