 ///
 /// @file    DictProducer.h
 /// @author  liweihang
 /// @date    2018-05-26 17:12:19
 ///

#ifndef __LWH_DICTPRODUCER_H
#define __LWH_DICTPRODUCER_H
#include <vector>
#include <map>
#include <string>
namespace lwh
{	
	class DictProducer
	{
		public:
			DictProducer(const std::string &dir);
			//DictProducer(const string &dir,SplitTool * splitTool);

			void build_dict();
			void build_cn_dict();
			void store_dict(const char * filepath);
			void show_files() const;
			void show_dict() const;
			void get_files();
			void push_dict(const std::string &word);
		private:
			std::string dir_;
			std::vector<std::string> files_;
			std::map<std::string,int> dict_;
			//SplitTool * splitTool_;
	};
}
#endif
