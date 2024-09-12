/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:45 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/12 15:02:32 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

static void	complete_cd(char *path, char **env)
{
	if (ft_strcmp(path, "--") == 0)
	{
		path = ft_getenv("HOME", env);
		if (path == NULL)
		{
			g_exit_status = 1;
			ft_putstr_fd("cd: HOME not set\n", 2);
		}
		else
			chdir(path);
	}
	else if (path[0] == '-' && path[1] == '\0')
	{
		path = ft_getenv("OLDPWD", env);
		if (path == NULL)
		{
			g_exit_status = 1;
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		}
		else
		{
			chdir(path);
			printf("%s\n", path);
		}		
	}
	else
	{
		if(chdir(path) == -1)
		{
			g_exit_status = 1;
			ft_putstr_fd("cd: No such file or directory\n", 2);
		}
	}
}

void	ft_cd(t_command *list, char **env)
{
	char	*path;

	if (list->arg[1] == NULL || list->arg[1][0] == '\0')
	{
		path = ft_getenv("HOME", env);
		if (path == NULL)
		{
			g_exit_status = 1;
			ft_putstr_fd("cd: HOME not set\n", 2);
		}
		else
			chdir(path);
	}
	else
	{
		path = list->arg[1];
		if (path[0] == '~')
		{
			path = getenv("HOME");
			chdir(path);
		}
		else
			complete_cd(path, env);
	}
}

