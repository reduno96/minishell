/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/30 12:50:27 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hundle_redirections(t_command *list)
{
	t_redirect	*tmp;

	tmp = list->doc;
	while (tmp != NULL)
	{
		if (tmp->type == REDIR_OUT)
		{
			hundle_redir_out(tmp->store);
		}
		else if (tmp->type == REDIR_IN)
		{
			hundle_redir_in(tmp->store);
		}
		else if (tmp->type == DREDIR_OUT)
		{
			hundle_dredir_out(tmp->store);
		}
		tmp = tmp->next;
	}
}

void	built_in(t_envarment *var, t_command *list, char **env)
{
	if (list == NULL)
		return ;
	if (ft_strcmp(list->content, "exit") == 0)
		(ft_exit(var, list));
	if (ft_strcmp(list->content, "cd") == 0)
		(ft_cd(list));
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
		(ft_echo(list, env));
	else
		return ;
}

void	execution_cmd(t_command *list, char **new, char **env)
{
	char	*ptr;

	(void)list;
	if (new[0][0] == '/')
		ptr = new[0];
	else
		ptr = path_command(new[0]);
	if (!ptr)
	{
		ft_putstr_fd("command not found\n", 2);
		exit(127);
	}
	if (execve(ptr, new, env) == -1)
		perror("execve");
	if (access(ptr, X_OK) == -1)
	{
		printf("minishell: %s: No access to path \n", new[0]);
		exit(126);
	}
}

int	built_in_exist(t_command *list)
{
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

void	ft_exute(t_envarment *var, t_command *list, char **env)
{
	int		fd;
	int		status;
	int		pid;

	(void)var;
	if (list == NULL  )
		return ;
		
	if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& herdoc_exist(list) == 0 && test_redir_here_doc(list) == 0)
	{
		if (test_redir_here_doc(list) == 1)
			hundle_redirections(list);
		built_in(var, list, env);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		if (herdoc_exist(list) == 1) // && pipe_exist(list) == 0)
		{
			fd = handle_here_doc(list, env);
			if (fd != -1)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			execution_cmd(list, list->arg, env);
		}
		if (pipe_exist(list) == 1)
		{
			fd = handle_pipe(list, env);
			if (fd != -1)
			{
				dup2(fd, STDOUT_FILENO);
				close(fd);
			}
		}
		else /// if (pipe_exist(list) == 0 && herdoc_exist(list) == 0)
		{
			if (test_redir_here_doc(list))
			{
				hundle_redirections(list);
				built_in(var, list, env);
			}
			if (built_in_exist(list) == 0)
				execution_cmd(list, list->arg, env);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
	}
}
