//Use of strftime
#include<stdio.h>
#include<time.h>

int main()
{
	char buf[32] = {0};
	struct tm *mytime;
	time_t tm;

	tm= time(NULL);
	mytime = localtime(&tm);

	//2017-07-02 18:39:30
	strftime(buf,sizeof(buf)-1,"%Y-%m-%d %H:%M:%S",mytime);
	printf ("Date and Time = %s\n",buf);
	return 0;
}
//एक महान यशगाथा
/*
   Testing output:

   Date and Time = 2017-07-02 18:38:34
 */
