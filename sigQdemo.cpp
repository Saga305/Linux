/*

Demo of sigqueue.

SagaTheReallyGreat@SagaTheReallyGreat-Inspiron-5520:~/Practice/data_structure$ c++ -g sigQdemo.cpp -lpthread -o test
SagaTheReallyGreat@SagaTheReallyGreat-Inspiron-5520:~/Practice/data_structure$ ./test
Signal handled and waiting for the signal for child thread
Signal sent successfully!!
Signal No: 12 Data: SagaTheGreat
SagaTheReallyGreat@SagaTheReallyGreat-Inspiron-5520:~/Practice/data_structure$ 

*/

#include<iostream>
#include<signal.h>
#include<cstdio>
#include<unistd.h>
#include<cstring>
#include<cstdlib>
#include <sys/types.h>
#include<pthread.h>

using namespace std;

void handler(int sig, siginfo_t *info, void *arg)
{
	void *data = info->si_value.sival_ptr;
	cout<<"Signal No: "<<sig<<" Data: "<<(char*)data<<endl;
}

void *myFun(void *var)
{
	union sigval value;
	int pid = *((int *) var);

	char *p = new char[20];
	strcpy(p,"SagaTheGreat");
	value.sival_ptr = (void*) p;
	if(sigqueue(pid, SIGUSR2, value) == 0)
	{
		cout<<"Signal sent successfully!!"<<endl;
	}
	else
	{
		perror("SIGSENT-ERROR:");
	}

	sleep(1);
	delete p;
	p = NULL;

	return NULL;
}

int main()
{
	pthread_t thread_id;
	int pid;
	struct sigaction action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &handler;

	if (sigaction(SIGUSR2, &action, NULL) == -1)
	{
		perror("sigusr: sigaction");
		return 0;
	}
	pid = getpid();

	cout<<"Signal handled and waiting for the signal from child thread"<<endl;

	pthread_create(&thread_id, NULL, myFun, &pid);

	pthread_join(thread_id, NULL);

	return 0;
}
