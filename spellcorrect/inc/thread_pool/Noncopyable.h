 ///
 /// @file    Noncopyable.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2017-11-24 10:55:36
 ///
 
#ifndef __LWH_NONCOPYABLE_H__
#define __LWH_NONCOPYABLE_H__

namespace lwh
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

	Noncopyable(const Noncopyable &) = delete;
	Noncopyable & operator=(const Noncopyable &) =delete;
};

}
#endif

