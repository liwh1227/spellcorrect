 ///
 /// @file    TcpServer.h
 /// @author  liweihang
 /// @date    2018-05-25 18:17:38
 ///

#ifndef __LWH_TCPSERVER_H
#define __LWH_TCPSERVER_H

#include "Acceptor.h"
#include "EpollPoller.h"
#include <string>
using std::string;
namespace lwh
{

class TcpServer
{
public:
	typedef EpollPoller::EpollCallback TcpServerCallback;
	TcpServer(const string &ip,unsigned short port);
	TcpServer(unsigned short port);
	
	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);
private:
	Acceptor acceptor_;
	EpollPoller poller_;

	TcpServerCallback connectionCallback_;
	TcpServerCallback messageCallback_;
	TcpServerCallback closeCallback_;
};
}

#endif
