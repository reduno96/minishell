/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:45 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/24 20:21:45 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_setenv_list(t_environment **var, char *old, char **env)
{
	t_environment	*my_var;
	t_environment	*my_var_1;
	char		*path;

	my_var = *var;
	my_var_1 = *var;
	my_var = find_env(*var, old);
	if (my_var != NULL)
	{
		free(my_var->data);
		my_var->data =NULL;
		if(ft_getenv("PWD",env) != NULL)
			my_var->data = ft_strdup(ft_getenv("PWD", env));
	}
	my_var_1 = find_env(*var, "PWD");
	if (my_var_1 != NULL)
	{
		free(my_var_1->data);
			my_var_1->data =NULL;
		path = getcwd(NULL, 0);
		if (path != NULL)
		{
			my_var_1->data = ft_strdup(path);
			free(path);
		}
	}
}

void	complete_cd_1(t_environment **var, char *path, char **env)
{
	(void)var;
	if (ft_strcmp(path, "--") == 0)
	{
		path = ft_getenv("HOME", env);
		if (chdir(path) == -1)
			printf_error_cd("cd: HOME not set", 1);
	}
	else if (path[0] == '-' && path[1] == '\0')
	{
		path = ft_getenv("OLDPWD", env);
		if (path == NULL)
			printf_error_cd("cd: OLDPWD not set", 1);
		else
		{
			chdir(path);
			printf("%s\n", path);
		}
	}
	else if (chdir(path) == -1)
	{
		g_exit_status = 1;
		perror("cd");
	}
}

void	complete_cd(char *path, char *ptr, char **env)
{
	path = ft_getenv("HOME", env);
	if (ptr[1] == '/')
		path = ft_strjoin_1(path, ft_strchr(ptr, '/'));
	if (path == NULL)
		printf_error_cd("cd: HOME not set", 1);
	else if (chdir(path) == -1)
	{
		g_exit_status = 1;
		perror("cd");
	}
}

void	ft_cd(t_environment **var, t_command *list, char **env)
{
	char	*path;

	if (list->arg[1] == NULL || list->arg[1][0] == '\0')
	{
		path = ft_getenv("HOME", env);
		if (path == NULL)
			printf_error_cd("cd: HOME not set", 1);
		else if (chdir(path) == -1)
		{
			g_exit_status = 1;
			perror("cd");
		}
	}
	else
	{
		path = list->arg[1];
		if (path[0] == '~')
			complete_cd(path, list->arg[1], env);
		else
			complete_cd_1(var, path, env);
	}
	ft_setenv_list(var, "OLDPWD", env);
}
