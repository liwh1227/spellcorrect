 
#ifndef __LWH_ACCEPTOR_H__
#define __LWH_ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace lwh
{

class Acceptor
{
public:
	Acceptor(int listenfd, const InetAddress & addr);

	void ready();
	int accept();

	int fd() const{	return listenSock_.fd();}
private:
	void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();

private:
	Socket listenSock_;
	InetAddress addr_;
};


}//end of namespace lwh

#endif
