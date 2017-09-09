//Run below code and verify the round robin scheduling.

#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void *thread1(void *arg)
{
	struct sched_param p;
	struct timespec tp;
	int my_policy;
	if(pthread_getschedparam(pthread_self(),&my_policy,&p))
	{
		perror("pthread_getschedparam");
	}

	while(1)
	{
		if(sched_rr_get_interval(0,&tp))
		{
			perror("sched_sched_rr_get_interval");
		}

		printf("Thread1 sched priority = %d and time interval sec = %ld nano sec = %ld\n",p.sched_priority,tp.tv_sec,tp.tv_nsec);
	}
	return NULL;

}

void *thread2(void *arg)
{
	struct sched_param p;
	struct timespec tp;
	int my_policy;
	if(pthread_getschedparam(pthread_self(),&my_policy,&p))
	{
		perror("pthread_getschedparam");
	}

	while(1)
	{
		if(sched_rr_get_interval(0,&tp))
		{
			perror("sched_sched_rr_get_interval");
		}

		printf("Thread2 sched priority = %d and time interval sec = %ld nano sec = %ld\n",p.sched_priority,tp.tv_sec,tp.tv_nsec);

	}
	return NULL;

}

void create(pthread_t* t,void *(*pf)(void *),int n)
{
	int status;
	pthread_attr_t thread_attr;
	struct sched_param thread_param;

	if(pthread_attr_init(&thread_attr))
	{
		perror("error pthread_attr_init");
		exit(1);
	}

	if(pthread_attr_setschedpolicy(&thread_attr,SCHED_RR))
	{
		perror("error pthread_attr_setschedpolicy");
		exit(1);
	}

	printf("min priority = %d\n",sched_get_priority_min(SCHED_RR));

	if(n == 1)
	{
		thread_param.sched_priority=sched_get_priority_min(SCHED_RR)+1;
	}
	else
	{
		thread_param.sched_priority=sched_get_priority_max(SCHED_RR)-1;
	}

	if(pthread_attr_setschedparam(&thread_attr,&thread_param))
	{
		perror("error pthread_attr_setschedparam");
		exit(1);
	}

	if(pthread_attr_setinheritsched(&thread_attr,PTHREAD_EXPLICIT_SCHED))
	{
		perror("error pthread_attr_setinheritsched");
		exit(1);
	}

	status=pthread_create(t,
			&thread_attr,
			pf,
			NULL
			);

	if(status!=0)
	{
		if(status==EPERM)
		{
			fprintf(stderr,"pthread_create() got EPERM\n");
		}
		else if(status==EINVAL)
		{
			fprintf(stderr,"pthread_create() got EINVAL\n");
		}
		else
		{
			fprintf(stderr,"pthread_create() got neither EPERM nor EINVAL\n");
		}

		fprintf(stderr,"pthread_create() got error %d\n",status);
		errno=status;
		perror("pthread_create");
		exit(1);
	}
}

int main(void)
{
	pthread_t th1,th2;
	create(&th1,thread1,1);
	create(&th2,thread2,2);

	if(pthread_join(th1,NULL))
	{
		fprintf(stderr,"error pthread_join()\n");
		exit(1);
	}

	if(pthread_join(th2,NULL))
	{
		fprintf(stderr,"error pthread_join()\n");
		exit(1);
	}

	return 0;

}
