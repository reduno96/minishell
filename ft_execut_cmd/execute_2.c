/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:22:56 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/16 19:16:22 by bouhammo         ###   ########.fr       */
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
void	built_in(t_envarment **var, t_command *list)
{
	if (list == NULL)
		return ;
	if (ft_strcmp(list->content, "exit") == 0)
		(ft_exit(var, list));
	if (ft_strcmp(list->content, "cd") == 0)
		(ft_cd(var,list, list->ar_env));
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



void	execution_cmd(t_command *list, char **new)
{
	char	*ptr;

	if (list == NULL || new == NULL || new[0] == NULL || list->ar_env == NULL)
		return ;
	if (new[0][0] == '/')
		ptr = new[0];
	else
		ptr = path_command(new[0], list->ar_env);
	if (!ptr)
	{
		ft_putstr_fd("command not found\n", 2);
		g_exit_status = 127;
		exit(127);
	}
	ft_access(ptr, new);
	if (execve(ptr, new, list->ar_env) == -1)
	{
		free(ptr);
		g_exit_status = 127;
		exit(127);
	}
}



void	run_simple_cmd(t_command *list, t_envarment **var)
{
	if (test_redir_here_doc(list) == 1)
	{
		hundle_redirections(list);
		built_in(var, list);
	}
	if (built_in_exist(list) == 0)
	{
		execution_cmd(list, list->arg);
	}
}





int	run_herdoc_built(t_envarment **var, t_command *cmd)
{
	t_command	*list;

	list = cmd;
	if (list == NULL)
		return (-1);
	if (herdoc_exist(list) == 1)
	{
		handle_here_doc(var, list);
		if (built_in_exist(list) == 1 && pipe_exist(list) == 0)
			built_in(var, list);
	}
	if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& herdoc_exist(list) == 0 && test_redir_here_doc(list) == 0)
	{
		if (test_redir_here_doc(list) == 1)
			hundle_redirections(list);
		built_in(var, list);
		return (1);
	}
	return (0);
}