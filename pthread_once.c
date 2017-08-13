/* Demo for pthread_once.

pthread_once_t once_control = PTHREAD_ONCE_INIT;
  pthread_once() - call an initialization routine only once

  int pthread_once(pthread_once_t *once_control,void (*init_routine)(void));

Parameters:

The macro PTHREAD_ONCE_INIT is used to statically initialize a once control block.This initialization must be done before calling pthread_once()

once_control:
Pointer  to  the  once-control  object  associated  with  the  one-time  initialization  function init_routine().

init_routine:
The  one-time  initialization  routine.   This  routine  is  called  only  once,  regardless  of  the number of times it and its associated
once_control are passed to pthread_once().

compilation command line:
gcc -pthread -Wall pthread_once.c -o test

Test results:
H1@Sga:~/Linux$ ./test 
Intialization Done
inside First thread
inside Second thread
H1@Sga:~/Linux$ ./test 
Intialization Done
inside Second thread
inside First thread
*/

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pthread_once_t once_control = PTHREAD_ONCE_INIT;

void init( void )
{
	printf("Intialization Done\n");
}

void *thread1(void *arg)
{

	pthread_once( &once_control, init );
	printf("inside First thread\n");
	return NULL;

}

void *thread2(void *arg)
{
	pthread_once( &once_control, init );
	printf("inside Second thread\n");
	return NULL;

}

void create(pthread_t* t,void *(*pf)(void *),int n)
{
	int                status;

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
	srand(getpid());
	int r = rand() % 2 + 1;
//Randomization in thread creation.
	if(r == 2)
	{
		create(&th2,thread2,2);
		create(&th1,thread1,1);
	}
	else
	{
		create(&th1,thread1,1);
		create(&th2,thread2,2);
	}


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

