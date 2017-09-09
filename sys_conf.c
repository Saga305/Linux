//एक महान यशगाथा
//sysconf example in unix
#include<stdio.h>
#include<unistd.h>
int main() {
	long ret = 0;

	//The maximum number of simultaneous processes per user ID.
	//you can verify it by using command line 'ulimit -u'
	//Also you can verify it by the g3etrlimit systemcall
	ret = sysconf(_SC_CHILD_MAX);
	fprintf(stdout,"Maximum child allowed = %lu\n",ret);

	//Maximum length of a hostname, not including the terminating null byte.
	//You can verify it by the command line 'getconf HOST_NAME_MAX'.
	ret = sysconf(_SC_HOST_NAME_MAX);
	fprintf(stdout,"Maximum length of hostname = %lu\n",ret);

	//Maximum length of a login name, including the terminating null byte.
	//You can verify it by the command line 'getconf LOGIN_NAME_MAX'
	ret = sysconf(_SC_LOGIN_NAME_MAX);
	fprintf(stdout,"Maximum length of Login name = %lu\n",ret);

	//Maximum number of supplementary group IDs.
	//You can verify it by the command line 'getconf NGROUPS_MAX'
	ret = sysconf(_SC_NGROUPS_MAX);
	fprintf(stdout,"Maximum number of supplementary group ID's = %lu\n",ret);

	//The number of clock ticks per second.
	ret = sysconf(_SC_CLK_TCK);
	fprintf(stdout,"The number of clock ticks per second = %lu\n",ret);

	//The maximum number of files that a process can have open at any time.
	//You can verify it by the command line "getconf OPEN_MAX" and "ulimit -n"
	ret = sysconf(_SC_OPEN_MAX);
	fprintf(stdout,"Max open files = %lu\n",ret);

	//Size of a page in bytes
	//You can verify it by the command line 'getconf PAGESIZE'
	ret = sysconf(_SC_PAGESIZE);
	fprintf(stdout,"Page size in bytes = %lu\n",ret);

	//The maximum number of streams that a process can have open at any time.
	//You can verify it by the command line 'getconf STREAM_MAX'
	ret = sysconf(_SC_STREAM_MAX);
	fprintf(stdout,"Max number of stream = %lu\n",ret);

	//Like this there are many macros you can check into the man page of sysconf.
	//if your cusor is on the standard function or system call name shift + k will direcly display the man page.

	return 0;
}
