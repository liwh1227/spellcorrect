 ///
 /// @file    Configuration.h
 /// @author  liweihang
 /// @date    2018-05-27 01:40:03
 ///

#ifndef __LWH_CONFIGURATION_H
#define __LWH_CONFIGURATION_H
#include <string>
#include <map>
namespace lwh
{
	class Configuration
	{
		public:
			static Configuration * getInstance();
			std::map<std::string,std::string> & getConfigMap();
			bool init(const std::string & filename);
			void show();
		private:
			Configuration(){}
			~Configuration(){}
		private:
			static Configuration * pInstance_;
			std::map<std::string,std::string> _configMap;
	};
}
#endif
