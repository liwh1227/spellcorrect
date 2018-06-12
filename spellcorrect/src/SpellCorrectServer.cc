 ///
 /// @file    SpellCorrectServer.cc
 /// @author  liweihang
 /// @date    2018-05-28 18:04:04
 ///

#include "../inc/SpellCorrectServer.h"
#include "../inc/Configuration.h"
#include "../inc/cache/CacheManager.h"
#include "../inc/MyDict.h"
#include "../inc/MyTask.h"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <functional>

using std::cout;
using std::endl;

namespace lwh
{
	SpellcorrectServer::SpellcorrectServer()
	:_tcpServer(Configuration::getInstance()->getConfigMap()["ip"],
			    atoi(Configuration::getInstance()->getConfigMap()["port"].c_str()))	
	,_threadpool()
	,_timer(std::bind(&CacheManager::updateCache),
			atoi(Configuration::getInstance()->getConfigMap()["init_time"].c_str()),
			atoi(Configuration::getInstance()->getConfigMap()["update_time"].c_str()))
	{
		MyDict * pMyDict = MyDict::createInstance();
		pMyDict->init(Configuration::getInstance()->getConfigMap()["endict"].c_str(),
				      Configuration::getInstance()->getConfigMap()["cndict"].c_str());
	}
	
	void SpellcorrectServer::start()
	{	
		_threadpool.start();
		
		using namespace std::placeholders;
		_tcpServer.setConnectionCallback(std::bind(&SpellcorrectServer::onConnection,this,_1));
		_tcpServer.setMessageCallback(std::bind(&SpellcorrectServer::onMessage,this,_1));
		_tcpServer.setCloseCallback(std::bind(&SpellcorrectServer::onClose,this,_1));
		
		_timer.start();
		_tcpServer.start();
	}
	
	void SpellcorrectServer::onConnection(const lwh::TcpConnectionPtr & conn)
	{
		cout << "\n>" << conn->toString() << "has connected!" << endl;
		conn->send("> welcome to SpellCorrect Server!");
	}

	void SpellcorrectServer::onMessage(const lwh::TcpConnectionPtr & conn)
	{
		string msg = conn->receive();
		MyTask task(msg,conn);
		using namespace std::placeholders;
		_threadpool.addTask(std::bind(&MyTask::execute,task));
	}

	void SpellcorrectServer::onClose(const TcpConnectionPtr & conn)
	{
		cout << "\n>" << conn->toString() << "has closed!" << endl;
	}
}
