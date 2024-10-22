///
/// @file    TcpConnection.h

#ifndef _LWH_TCPCONNCETION_H
#define _LWH_TCPCONNCETION_H

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

namespace lwh
{	
	class EpollPoller;
	class TcpConnection;
	typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

	class TcpConnection
	: Noncopyable
	,public std::enable_shared_from_this<TcpConnection>	
	{
		public:
			typedef std::function<void(const TcpConnectionPtr&)> TcpConnectionCallback;
			TcpConnection(int sockfd,EpollPoller *loop);
			~TcpConnection();

			std::string receive();
			void send(const std::string & msg);
			void sendInLoop(const std::string & msg);
			void shutdown();

			std::string toString();

			void setConnectionCallback(TcpConnectionCallback cb);
			void setMessageCallback(TcpConnectionCallback cb);
			void setCloseCallback(TcpConnectionCallback cb);

			void handleConnectionCallback();
			void handleMessageCallback();
			void handleCloseCallback();
		private:
			Socket sockfd_;
			SocketIO sockIO_;
			const InetAddress localAddr_;
			const InetAddress peerAddr_;
			bool isShutdownWrite_;
			EpollPoller * loop_;

			TcpConnectionCallback onConnectionCb_;
			TcpConnectionCallback onMessageCb_;
			TcpConnectionCallback onCloseCb_;
	};

}//end of namespace lwh 

#endif
