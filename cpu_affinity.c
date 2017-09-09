//CPU affinity on threads code and testing details.

#define _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

void f()
{
	while(1);
}

void *thread1(void *arg)
{
	const pthread_t pid = pthread_self();
	const int core_id = 1;

	printf("Thread1 tid = %lu\n",syscall(SYS_gettid));

	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(core_id, &cpuset);

	if(pthread_setaffinity_np(pid, sizeof(cpu_set_t), &cpuset))
	{

		perror("pthread_setaffinity_np");
	}

	if(pthread_getaffinity_np(pid, sizeof(cpu_set_t), &cpuset))
	{
		perror("pthread_getaffinity_np");
	}

	if (CPU_ISSET(core_id, &cpuset))
	{
		printf("1::SUCCESS\n");
	}
	else
	{
		printf("1::FAIL\n");
	}

	f();

	return NULL;
}

void *thread2(void *arg)
{
	const pthread_t pid = pthread_self();
	const int core_id = 2;

	printf("Thread2 tid = %lu\n",syscall(SYS_gettid));

	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(core_id, &cpuset);

	if(pthread_setaffinity_np(pid, sizeof(cpu_set_t), &cpuset))
	{

		perror("pthread_setaffinity_np");
	}

	if(pthread_getaffinity_np(pid, sizeof(cpu_set_t), &cpuset))\
	{
		perror("pthread_getaffinity_np");
	}

	if (CPU_ISSET(core_id, &cpuset))
	{
		printf("2::SUCCESS\n");
	}
	else
	{
		printf("2::FAIL\n");
	}

	f();

	return NULL;
}

void create(pthread_t* t,void *(*pf)(void *),int n)
{
	int status;
	status=pthread_create(t,
			NULL,
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
/*
Testings:

=>Compile:: gcc -pthread -Wall wje_q.c -o test

=>Execute the binary::
एक महान यशगाथा@एक महान यशगाथा:~/practice$ ./test
Thread1 tid = 5164 //Thread-1
Thread2 tid = 5165 //Thread-2
1::SUCCESS
2::SUCCESS

=> Check the process and created thread by that process::
एक महान यशगाथा@एक महान यशगाथा:~/practice$ ps -e -T | grep test
5163 5163 pts/11 00:00:00 test //main Thread
5163 5164 pts/11 00:00:49 test //Thread-1
5163 5165 pts/11 00:00:49 test //Thread-2

=> Verify the CPU affinity::
एक महान यशगाथा@एक महान यशगाथा:~/practice$ taskset -c -p 5164
pid 5164's current affinity list: 1
एक महान यशगाथा@एक महान यशगाथा:~/practice$ taskset -c -p 5165
pid 5165's current affinity list: 2
 */
