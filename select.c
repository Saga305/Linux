//STDIN timeout using select system call.
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>

int main(void) {
	char buf[100];
	int ret;
	fd_set readfds; //read set
	struct timeval timeout; //for set the timeout time
	while(1) {
		FD_ZERO(&readfds); //clear a set
		FD_SET(STDIN_FILENO,&readfds); //add a set
		timeout.tv_sec=5; //set tiemout of 5 sec
		timeout.tv_usec=0;
		ret = select(1,&readfds,NULL,NULL,&timeout);
		if(0 == ret) //select will return zero when timeout expires
		{
			//if there is not any input into STDIN for 5 second then it will display timeout print at STDOUT
			printf("Timeout\n");
		}
		else
		{
			memset(buf,'\0',sizeof(buf));
			ret = read(STDIN_FILENO,buf,sizeof(buf));

			if(ret != -1 ) {
				write(STDOUT_FILENO,buf,sizeof(buf));
			}
		}
	}
	return 0;
}
//!-- एक महान यशगाथा --!//
