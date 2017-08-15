/* Demo for thread specific data key API '''pthread_key_create'''
#include <pthread.h>

int pthread_key_create(pthread_key_t *key, void (*destructor)(void *));

General description

Creates a key identifier, associated with key, and returns the key identifier into the storage area of type pthread_key_t. At this point, each of the threads in the application has the use of that key, and can set its own unique value by use of pthread_setspecific(). A thread can get its own unique value using pthread_getspecific().
The destructor routine may be called when the thread ends. It is called when a non-NULL value has been set for the key for this thread, using pthread_setspecific(), and the thread:

    Calls pthread_exit()
    Does a return from the start routine
    Is canceled because of a pthread_cancel() request.

When called, the destructor routine is passed the value bound to the key by the use of pthread_setspecific().
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_key_t buffer_key;

void buffer_key_destruct( void *value )
{
	printf("buffer_key_destruct %s\n",(char *)value);
	free( value );
	pthread_setspecific( buffer_key, NULL );
}

char *checkup( void )
{
	char *string;
	string = (char *)pthread_getspecific( buffer_key );
	if( string == NULL ) {
		string = (char *) malloc( 32 );
		sprintf( string, "Thread Id =  %lu\n", pthread_self() );      
		pthread_setspecific( buffer_key, (void *)string );
	}
	return( string );
}

void *function( void *arg )
{
	printf("thread1 %s\n",checkup());
	sleep(30);
	printf("thread1 %s\n",checkup());
	return( 0 );
}

void *function1( void *arg )
{
	printf("thread2 %s\n",checkup());
	sleep(30);
	printf("thread2 %s\n",checkup());
	return( 0 );
}

int main( void )
{
	pthread_t t1,t2;
	pthread_key_create( &buffer_key,&buffer_key_destruct);
	pthread_create( &t1, NULL, &function, NULL );
	pthread_create( &t2, NULL, &function1, NULL );
	sleep( 60 );
	return 0;
}
