/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execur_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:58 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/12 15:23:25 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_exist(t_command *list)
{
	t_command	*tmp;

	if(list == NULL)
		return 0;

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

void	close_free_wait(int *pids, int **pipefd, int num_cmd,
		t_command *tmp_cmd)
{
	(void)tmp_cmd;
	int	i;
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
		j++;
	}
	i = 0;
	free(pids);
	while (i < num_cmd - 1)
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
}

void	handle_pipe(t_command *list, t_envarment **var)
{
	int			num_cmd;
	int			**pipefd;
	char		**arr_env;
	t_command	*tmp_cmd;
	pid_t		*pids;
	int			heredoc_fd;
	int			i;
	char		*ptr;

	num_cmd = num_pipe(list) + 1;
	pipefd = return_pipe(num_cmd);
	arr_env = array_env(var);
	tmp_cmd = list;
	pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
	heredoc_fd = -1;
	i = 0;
	if (!pids)
	{
		perror("malloc");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	while (i < num_cmd)
	{
		if (tmp_cmd->is_pipe == 1)
		{
			tmp_cmd = tmp_cmd->next;
		}
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			g_exit_status = 1;
			exit(EXIT_FAILURE);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			g_exit_status = 1;
			exit(EXIT_FAILURE);
		}
		if (pids[i] == 0)
		{
			if (i > 0)
			{
				close(pipefd[i - 1][1]);
				dup2(pipefd[i - 1][0], STDIN_FILENO);
				close(pipefd[i - 1][0]);
			}
			if (i < num_cmd - 1)
			{
				close(pipefd[i][0]);
				dup2(pipefd[i][1], STDOUT_FILENO);
				close(pipefd[i][1]);
			}
			if (built_in_exist(tmp_cmd) && tmp_cmd->arg[1] == NULL)
			{
				built_in(var, tmp_cmd);
				g_exit_status = 0;
				exit(EXIT_SUCCESS);
			}
			if (test_redir_here_doc(tmp_cmd))
			{
				hundle_redirections(tmp_cmd);
			}
			if (tmp_cmd->her != NULL)
			{
				heredoc_fd = hundle_file_herdoc(tmp_cmd);
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
			ptr = path_command(tmp_cmd->content, arr_env);
			printf("---------------------------->>>>>>>>>>>>>>>>>>.    %s\n\n", ptr);
			if(access(ptr , X_OK) == -1)
			{
				ft_putstr_fd("++++ command not found \n", 2);
				g_exit_status = 1;
				exit(EXIT_FAILURE);
			}
			execve(ptr, tmp_cmd->arg, arr_env);
				perror("execve failed ");
		}
		if (i > 0)
		{
			close(pipefd[i - 1][0]);
			close(pipefd[i - 1][1]);
		}
		tmp_cmd = tmp_cmd->next;
		i++;
	}
	close_free_wait(pids, pipefd, num_cmd, tmp_cmd);
}
////////////////////////////////////////////


