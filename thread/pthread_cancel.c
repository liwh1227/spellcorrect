 ///
 /// @file    pthread_cancel.c
 /// @author  liweihang
 /// @date    2018-03-22 00:55:00
 ///
 
#include "func.h"

void * threadfunc(void *p)
{
	printf("i am thread1\n");
	sleep(2);
	printf("1234567\n");

	return NULL;
}

int main()
{
	pthread_t pthid;

	int ret = pthread_create(&pthid,NULL,threadfunc,NULL);
	if(ret != 0)
	{
		printf("the pthread_create is error,errornum is %d\n",ret);
		return -1;
	}
	
	pthread_cancel(pthid);
	
	pthread_join(pthid,NULL);
	printf("i am main thread\n");

	return 0;
}
