 ///
 /// @file    pthread_cancel.c
 /// @author  liweihang
 /// @date    2018-03-22 00:55:00
 ///
 
#include "func.h"
void cleanup(void *p)
{
	printf("i am cleanup func,*p = %s\n",(char *)p);
	free(p);
}

void * threadfunc(void *p)
{
	p = (char *)malloc(10);
	strcpy(p,"hello");
	
	pthread_cleanup_push(cleanup,p);
	sleep(2);
	pthread_cleanup_pop(0);
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
	
	ret = pthread_cancel(pthid);
	if(ret != 0)
	{
		printf("pthread_cancel error,errornum is %d\n",ret);
		return -1;
	}
	
	long l;
	pthread_join(pthid,(void **)&l);
	printf("i am main thread,%ld\n",l);

	return 0;
}
