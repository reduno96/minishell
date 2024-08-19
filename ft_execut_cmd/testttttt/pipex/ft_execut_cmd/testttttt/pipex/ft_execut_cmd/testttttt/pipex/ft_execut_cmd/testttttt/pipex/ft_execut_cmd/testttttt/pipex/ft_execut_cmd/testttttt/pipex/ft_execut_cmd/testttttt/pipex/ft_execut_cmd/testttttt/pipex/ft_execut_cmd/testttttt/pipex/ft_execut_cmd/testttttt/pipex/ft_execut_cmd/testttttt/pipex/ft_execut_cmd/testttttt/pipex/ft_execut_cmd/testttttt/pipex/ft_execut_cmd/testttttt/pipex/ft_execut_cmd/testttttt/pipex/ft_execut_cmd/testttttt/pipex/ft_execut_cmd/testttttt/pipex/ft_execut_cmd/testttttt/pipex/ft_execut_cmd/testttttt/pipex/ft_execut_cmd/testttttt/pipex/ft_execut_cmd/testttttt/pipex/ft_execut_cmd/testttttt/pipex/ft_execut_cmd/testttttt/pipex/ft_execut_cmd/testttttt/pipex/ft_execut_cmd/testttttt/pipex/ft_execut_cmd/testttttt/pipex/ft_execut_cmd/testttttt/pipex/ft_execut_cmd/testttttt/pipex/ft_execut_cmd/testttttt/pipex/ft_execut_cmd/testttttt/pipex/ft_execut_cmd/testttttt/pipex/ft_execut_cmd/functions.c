/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:09 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/18 10:58:53 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_strcmp(char *s1, char *s2)
{
	if(!s1 || !s2)
		return -1;
	int i =0;
	while((s1[i] == s2[i]) && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);

}
char **create_argv(t_splitor *elem) 
{
	int count = 0;
	char **argv;
	t_splitor *tmp ;

	tmp = elem;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tmp = elem;
	int i = 0;
	while (tmp)
	{
		argv[i] = ft_strdup(tmp->in);
		if(!argv[i])
		{
			int j = 0;
			while (j < i)
			{
				free(argv[j]);
				j++;
			}
		}
		i++;
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return argv;
}


char 	*path_command(char *ptr)
{
	char *path;
	char **list;
	int i=0;
	int a;
	char *tmp ;
	char *tmp2;

	path  = getenv("PATH");
	if(!path)
		perror("Error: PATH not found\n");
	
	list = ft_split(path, ':');
	while (list[i])
	{
		if(ptr[0] == '/')
			tmp2 = ptr;
		else
		{
			tmp = ft_strjoin(list[i], "/");
			tmp2 = ft_strjoin(tmp, ptr);
		}
		a = access(tmp2, F_OK) ;
		if (a == 0)
		{
			// free(ptr);
			return tmp2;
		}
		i++;
	}
	// free(ptr);
	ptr =NULL;
return ptr;
}
