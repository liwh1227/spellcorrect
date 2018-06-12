 ///
 /// @file    main.cc
 /// @author  liweihang
 /// @date    2018-05-26 19:31:41
 ///
 
#include "../inc/DictProducer.h" 
#include "../inc/Configuration.h"

using namespace lwh;

int main()
{	
	Configuration * p1 = Configuration::getInstance();
	p1->init("../conf/dict.conf");
	p1->show();

	DictProducer dictproducer(p1->getConfigMap()["yuliaofile"]);
	dictproducer.build_dict();
	dictproducer.build_cn_dict();
	dictproducer.store_dict("../../data/dict.data");
	return 0;
}

