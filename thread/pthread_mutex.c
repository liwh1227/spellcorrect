 ///
 /// @file    pthread_mutex.c
 /// @author  liweihang
 /// @date    2018-03-22 00:24:16
 ///

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define thread_num 5 

void * threadfunc(void * p)
{
	int  i = (int) p ;
	printf("i am thread%d\n",i);
	pthread_exit(NULL);
}

int main()
{
	pthread_t pthid[thread_num];
	int j;
	for(j = 0;j < thread_num;j++)
	{
		pthread_create(&(pthid[j]),NULL,threadfunc,(void *)j);
	}
	
	j = 100;

	int i;
	for(i = 0;i < thread_num;i++)
	{
		pthread_join(pthid[i],NULL);
	}
	
	return 0;
}
