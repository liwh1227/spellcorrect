 ///
 /// @file    test_server.cc
 /// @author  liweihang
 /// @date    2018-05-29 00:20:51
 ///

#include "../inc/Configuration.h"
#include "../inc/SpellCorrectServer.h"
#include "../inc/cache/CacheManager.h"
#include <stdlib.h>
#include <iostream>
using std::cout;
using std::endl;

using namespace lwh;
int main()
{
	Configuration::getInstance()->init("../conf/file.conf");
	Configuration::getInstance()->show();

	CacheManager::initCache(atoi(Configuration::getInstance()->getConfigMap()["thread_num"].c_str()),
							Configuration::getInstance()->getConfigMap()["cache"]);
	CacheManager::getCache(0).debug();
	lwh::SpellcorrectServer server;
	server.start();

	return 0;
}
