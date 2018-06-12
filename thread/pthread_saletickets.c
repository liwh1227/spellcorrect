 ///
 /// @file    pthread_saletickets.c
 /// @author  liweihang
 /// @date    2018-03-22 17:43:51
 ///
 
#include "func.h"

int tickets = 20;

typedef struct 
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
}ticket;

void * threadhandle(void * arg)
{	
	ticket * t = (ticket *) arg;
	pthread_mutex_lock(&t->mutex);
	while(1)
	{
		if(tickets > 0)
		{
			printf("thread1开始售票...%d\n",tickets);
			tickets --;
			sleep(2);
		}else
		{
			printf("票已售罄...\n");
			break;
		}
	}
	pthread_mutex_unlock(&t->mutex);
	pthread_exit((void *)1);
}

int main()
{	
	ticket t;
	pthread_t *pthid = (pthread_t *)calloc(3,sizeof(pthread_t));
	int ret = pthread_mutex_init(&t.mutex,NULL);
	if(ret != 0)
	{
		printf("pthread_mutex_init is wrong,the errornum is %d\n",ret);
		return -1;
	}
	
	ret = pthread_cond_init(&t.cond,NULL);
	if(ret != 0)
	{
		printf("pthread_mutex_init is wrong,the errornum is %d\n",ret);
		return -1;
	}
	int i;
	for(i = 0;i < 3;i++)
	{
		pthread_create(&pthid[i],NULL,threadhandle,&t);
	}

	int l;
	for(i = 0;i < 3;i++)
	{
		pthread_cancel(pthid[i]);
		pthread_join(pthid[i],(void **)&l);
		printf("thread%d 被收取\n",l);
	}
	
	pthread_mutex_destroy(&t.mutex);

	return 0;
}
