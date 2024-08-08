#include "../minishell.h"

void ft_pwd(t_command *list)
{
	(void)list;
	char *path ;
			path = getcwd(NULL, 0);
			if(path == NULL)
				return ;
			printf("%s\n", path);	
}