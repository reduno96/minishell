/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:02:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/27 10:34:27 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	built_in_exist(t_command *list)
{
	if (list == NULL)
		return (0);
	if (ft_strcmp(list->content, "exit") == 0)
		return (1);
	if (ft_strcmp(list->content, "cd") == 0)
		return (1);
	if (ft_strcmp(list->content, "pwd") == 0)
		return (1);
	if (ft_strcmp(list->content, "export") == 0)
		return (1);
	if (ft_strcmp(list->content, "unset") == 0)
		return (1);
	if (ft_strcmp(list->content, "env") == 0)
		return (1);
	if (ft_strcmp(list->content, "echo") == 0)
		return (1);
	return (0);
}

void	built_in(t_environment **var, t_command *list)
{
	if (list == NULL)
		return ;
	if (ft_strcmp(list->content, "exit") == 0)
		(ft_exit(var, list));
	if (ft_strcmp(list->content, "cd") == 0)
		(ft_cd(var, list));
	if (ft_strcmp(list->content, "pwd") == 0)
		(ft_pwd(list));
	if (ft_strcmp(list->content, "export") == 0)
	{
		(ft_export(var, list));
	}
	if (ft_strcmp(list->content, "unset") == 0)
		(ft_unset(var, list));
	if (ft_strcmp(list->content, "env") == 0)
		(ft_env(var));
	if (ft_strcmp(list->content, "echo") == 0)
	{
		(ft_echo(list));
	}
}

int	ft_str_eqal(char *ptr, char c)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == c)
			return (1);
		i++;
	}
	return (0);
}
