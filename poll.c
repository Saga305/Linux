//STDIN timeout using poll system call.
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<poll.h>

int main(void) {
	char buf[100];
	int ret;
	struct pollfd fds[1]; //array of file descriptors
	int timeout;

	while(1) {
		fds[0].fd = STDIN_FILENO;
		fds[0].events = 0;
		fds[0].events |= POLLIN; //There is a data to read

		timeout=5000; //set tiemout of 5 sec

		ret = poll(fds,1,timeout);
		if(0 == ret) //poll will return zero when timeout expires
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
