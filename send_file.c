//Use of sendfile system call.
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/sendfile.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("Usage:: %s sourceFile destionationFile\n",argv[0]);
		exit(1);
	}

	int fd1,fd2,ret;
	struct stat sbuf;

	fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0)
	{
		perror("open::read");
		exit(1);
	}
	//fstat will provide the attributes of open file descriptor into stat structure member passsed into formal arguments
	fstat(fd1,&sbuf);

	fd2 = open(argv[2],O_CREAT|O_WRONLY,0600);
	if(fd2 < 0)
	{
		perror("open::write");
		exit(1);
	}

	ret = sendfile(fd2,fd1,0,sbuf.st_size);
	if(ret < 0)
	{
		perror("sendfile::");
		exit(1);
	}
	else if(ret == sbuf.st_size)
	{
		printf("File is transfered successfully\n");
	}
	return 0;
}

/*
TESTINGS:
=========================================
TriumpH@एक महान यशगाथा:~/practise$ cat file1.txt
"जब जब ये बारिश की बूँदें मुझे छू ती है,

तब तब तेरा मेरे साथ बारिश में भीगना बोहोत याद आता है."
=========================================
TriumpH@एक महान यशगाथा:~/practise$ cc test.c -o sendfile
TriumpH@एक महान यशगाथा:~/practise$ ls
file1.txt sendfile test.c
=========================================
TriumpH@एक महान यशगाथा:~/practise$ ./sendfile
Usage:: ./sendfile sourceFile destionationFile
=========================================
TriumpH@एक महान यशगाथा:~/practise$ ./sendfile file1.txt file2.txt
File is transfered successfully
=========================================
TriumpH@एक महान यशगाथा:~/practise$ cat file2.txt
"जब जब ये बारिश की बूँदें मुझे छू ती है,

तब तब तेरा मेरे साथ बारिश में भीगना बोहोत याद आता है."
=========================================
 */
