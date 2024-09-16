/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:21:29 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/16 12:35:20 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"





int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		return (1);
	}
	return (0);
}

void	ft_access_2(char *ptr, char **str)
{
	if (access(ptr, F_OK) == -1 || access(ptr, X_OK) == -1)
	{
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd(": command not found\n", 2);
		if (ptr != str[0])
			free(ptr);
		g_exit_status = 127;
		exit(127);
	}
	else if (is_directory(ptr))
	{
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd(": command not found\n", 2);
		if (ptr != str[0])
			free(ptr);
		g_exit_status = 127;
		exit(127);
	}
}

void	ft_access_1(char *ptr, char **str)
{
	if (ptr[ft_strlen(ptr) - 1] == '/')
	{
		if (is_directory(ptr))
		{
			ft_putstr_fd(ptr, 2);
			ft_putstr_fd(": is a directory\n", 2);
			g_exit_status = 126;
			exit(126);
		}
		else
		{
			ft_putstr_fd(ptr, 2);
			ft_putstr_fd(": Not a directory\n", 2);
			g_exit_status = 126;
			exit(126);
		}
	}
	else
	{
		ft_access_2(ptr, str);
	}
}

void	ft_access(char *ptr, char **str)
{
	if (ptr == NULL || str == NULL || *str == NULL)
		return ;
	if (ft_strncmp(ptr, "./", 2) == 0 || ptr[0] == '/')
	{
		if (access(ptr, F_OK) == -1)
		{
			ft_putstr_fd(ptr, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			if (ptr != str[0])
				free(ptr);
			g_exit_status = 127;
			exit(127);
		}
		if (access(ptr, X_OK) == -1)
		{
			ft_putstr_fd(ptr, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			if (ptr != str[0])
				free(ptr);
			g_exit_status = 126;
			exit(126);
		}
		if (is_directory(ptr))
		{
			ft_putstr_fd(ptr, 2);
			ft_putstr_fd(": is a directory\n", 2);
			g_exit_status = 126;
			exit(126);
		}
	}
	ft_access_1(ptr, str);
}
