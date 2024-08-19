#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int ft_strlen(char *s)
{
	int i =0;
	while(s[i])
		i++;

	return i;
}

void 	reverse(char *s)
{
	int len = ft_strlen(s);
	int i =0;
	while(i  < len /2)
	{
		char *tmp = str[i];
		str[i] = str[len -i -1];
		str[len -i -1] =str[i]
	}
}

int main()
{
	int fd_p[2];
	int fs_c[2];

	char buffer[256];

	pipe(fd_p);
	pipe(fd_c);

	pid_t pid = fork();

	if(pid > 0)
	{

