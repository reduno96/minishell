/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/21 12:48:36 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_leaks(t_command *list, t_envarment **var)
{
	int	i;

	(void)var;
	i = 0;
	while (list->ar_env[i])
	{
		free(list->ar_env[i]);
		i++;
	}
	free(list->ar_env);
}

void	parent_proc(int pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		g_exit_status = 1;
	}
	else
	{
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

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

void	run_command(t_command *list, t_envarment **var)
{
	int	heredoc_fd;

	heredoc_fd = -1;
	if (herdoc_exist(list) == 1 && pipe_exist(list) == 0)
	{
		heredoc_fd = hundle_file_herdoc(list);
		if (heredoc_fd != -1)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		hundle_redirections(list);
		execution_cmd(list, list->arg);
		exit(0);
	}
	else if (pipe_exist(list) == 1)
	{
		handle_pipe(list, var);
		exit(g_exit_status);
	}
	else
	{
		run_simple_cmd(list, var);
		exit(0);
	}
}

void	ft_exute(t_envarment **var, t_command *cmd)
{
	t_command	*list;
	int			pid;

	list = cmd;

	list->ar_env = array_env(var);
	if (run_herdoc_built(var, cmd) == 1)
	{
		delet_files(cmd);
		ft_free_leaks(list, var);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
		run_command(list, var);
	else
		parent_proc(pid);
	delet_files(cmd);
	ft_free_leaks(list, var);
}

// void	printf_list_ar_env(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("tab[%d] -----------> %s \n", i, tab[i]);
// 		i++;
// 	}
// }
