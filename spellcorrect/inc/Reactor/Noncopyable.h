 ///
 /// @file    Noncopyable.h
 
#ifndef __LWH_NONCOPYABLE_H__
#define __LWH_NONCOPYABLE_H__

namespace lwh
{

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}
private:
	Noncopyable(const Noncopyable&);
	Noncopyable & operator=(const Noncopyable&);
};

}//end of namespace lwh

#endif
