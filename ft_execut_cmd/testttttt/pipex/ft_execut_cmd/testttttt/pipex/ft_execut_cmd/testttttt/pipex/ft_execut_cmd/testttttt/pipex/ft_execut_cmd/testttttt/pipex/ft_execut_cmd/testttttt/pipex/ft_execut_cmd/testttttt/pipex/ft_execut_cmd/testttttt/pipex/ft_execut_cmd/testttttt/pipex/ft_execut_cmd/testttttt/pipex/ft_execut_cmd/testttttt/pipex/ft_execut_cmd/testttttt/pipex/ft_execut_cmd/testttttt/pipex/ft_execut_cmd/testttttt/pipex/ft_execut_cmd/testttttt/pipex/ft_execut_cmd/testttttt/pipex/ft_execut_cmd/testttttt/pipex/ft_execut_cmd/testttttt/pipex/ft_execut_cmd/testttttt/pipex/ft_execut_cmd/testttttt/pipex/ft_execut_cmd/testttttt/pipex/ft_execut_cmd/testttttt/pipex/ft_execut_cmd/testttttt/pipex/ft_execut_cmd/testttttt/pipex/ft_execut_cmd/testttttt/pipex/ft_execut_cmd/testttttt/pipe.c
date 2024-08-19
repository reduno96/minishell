#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
int main()
{
	int fds[2];
	char buffer[256]= { 0 };

	printf("parent pid = %d\n", getpid());

	pipe(fds);
	write(fds[1] , "ABCD" , 4);
	if(fork() > 0)
	{
		return 0;
	}

	read(fds[0] , buffer , 4);
	printf("got from pipe %s \n", buffer);
	printf("child pid = %d \n", getpid());
}
