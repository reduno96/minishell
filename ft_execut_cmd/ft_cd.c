#include "../minishell.h"

void ft_cd(t_command *list)
{
	char *path ;

			if (list->arg[1] == NULL)
			{
				path = getenv("HOME");
				if (chdir(path) == -1)
					perror("No such file or directory");
			}
			else
			{
				path = list->arg[1];
				if (chdir(path) == -1)
					perror("No such file or directory");
			}
}
