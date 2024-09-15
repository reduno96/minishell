/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execur_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:58 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/15 13:43:18 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_exist(t_command *list)
{
	t_command	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	while (tmp)
	{
		if (tmp->is_pipe == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	num_pipe(t_command *list)
{
	t_command	*tmp;
	int			i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (tmp->is_pipe == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	**return_pipe(int num_cmd)
{
	int	**pipe;
	int	i;

	pipe = (int **)malloc(sizeof(int *) * num_cmd);
	if (!pipe)
	{
		perror("malloc");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_cmd)
	{
		pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe[i])
		{
			perror("malloc");
			g_exit_status = 1;
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe);
}

void 	free_pid_pipe(int *pids, int **pipefd, int num_cmd)
{
	int 	i;
	
	i = 0;
	if( pipefd != NULL)
	{
		while (i < num_cmd - 1)
		{
			free(pipefd[i]);
			i++;
		}
		free(pipefd);
	}
	if(pids != NULL)
	free(pids);
}
void	close_free_wait(int *pids, int **pipefd, int num_cmd)
{
	int	j;
	int	status;

	close(pipefd[num_cmd - 1][0]);
	close(pipefd[num_cmd - 1][1]);
	j = 0;
	while (j < num_cmd)
	{
		if (waitpid(pids[j], &status, 0) == -1)
		{
			perror("waitpid");
			g_exit_status = status;
			exit(status);
		}
		else
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
		j++;
	}
	free_pid_pipe(pids , pipefd , num_cmd);
}
void	ft_write_in_pipe(t_pipe *hd_p, int i)
{
	if (i > 0)
	{
		close(hd_p->pipefd[i - 1][1]);
		dup2(hd_p->pipefd[i - 1][0], STDIN_FILENO);
		close(hd_p->pipefd[i - 1][0]);
	}
	if (i < hd_p->num_cmd - 1)
	{
		close(hd_p->pipefd[i][0]);
		dup2(hd_p->pipefd[i][1], STDOUT_FILENO);
		close(hd_p->pipefd[i][1]);
	}
}
void	ft_func_2(t_pipe *hd_p, int i, t_envarment **var)
{
	if (hd_p->pids[i] == 0)
	{
		ft_write_in_pipe(hd_p, i);
		if (test_redir_here_doc(hd_p->tmp_cmd))
			hundle_redirections(hd_p->tmp_cmd);
		if (built_in_exist(hd_p->tmp_cmd) == 1)
		{
			built_in(var, hd_p->tmp_cmd);
			exit(EXIT_SUCCESS);
		}
		if (hd_p->tmp_cmd->her != NULL)
		{
			hd_p->heredoc_fd = hundle_file_herdoc(hd_p->tmp_cmd);
			dup2(hd_p->heredoc_fd, STDIN_FILENO);
			close(hd_p->heredoc_fd);
		}
		hd_p->ptr = path_command(hd_p->tmp_cmd->content, array_env(var));
		ft_access(hd_p->ptr, array_env(var));
		if (execve(hd_p->ptr, hd_p->tmp_cmd->arg, array_env(var)) == -1)
			exit(1);
	}
}
void	ft_func(t_pipe *hd_p, int i, t_envarment **var)
{
	if (hd_p->tmp_cmd->is_pipe == 1)
		hd_p->tmp_cmd = hd_p->tmp_cmd->next;
	if (pipe(hd_p->pipefd[i]) == -1)
	{
		perror("pipe");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	hd_p->pids[i] = fork();
	if (hd_p->pids[i] == -1)
	{
		perror("fork");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	ft_func_2(hd_p, i, var);
	if (i > 0)
	{
		close(hd_p->pipefd[i - 1][0]);
		close(hd_p->pipefd[i - 1][1]);
	}
	hd_p->tmp_cmd = hd_p->tmp_cmd->next;
}
void	handle_pipe(t_command *list, t_envarment **var)
{
	t_pipe	hd_p;
	int		i;

	// hd_p = NULL;
	hd_p.num_cmd = num_pipe(list) + 1;
	hd_p.pipefd = return_pipe(hd_p.num_cmd);
	hd_p.tmp_cmd = list;
	hd_p.pids = (pid_t *)malloc(sizeof(pid_t) * hd_p.num_cmd);
	hd_p.heredoc_fd = -1;
	i = 0;
	if (!hd_p.pids)
	{
		perror("malloc");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	while (i < hd_p.num_cmd)
	{
		ft_func(&hd_p, i, var);
		i++;
	}
	close_free_wait(hd_p.pids, hd_p.pipefd, hd_p.num_cmd);
}
