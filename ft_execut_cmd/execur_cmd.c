/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execur_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:58 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/05 11:10:21 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_exist(t_command *list)
{
	t_command	*tmp;

	tmp = list;
	while (tmp)
	{	
		if (tmp->content != NULL && tmp->content[0] == '|')
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
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_cmd)
	{
		pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipe[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipe);
}

t_command	*get_list_command(t_command *list)
{
	t_command	*tmp;
	t_command	*head;
	t_command	*prev;
	int i = 0;


	tmp = NULL;
	head = NULL;
	prev = NULL;
	while (list)
	{
		if (list->content[0] == '|')
			list = list->next;
		else
		{
			tmp = (t_command *)malloc(sizeof(t_command));
			if (!tmp)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			tmp->content = list->content;
			tmp->arg = list->arg;
			i=0;
			while (list->arg[i])
			{
				tmp->arg[i] = list->arg[i];
				i++;
			}
			tmp->doc = list->doc;
			tmp->store_her = list->store_her;
			i = 0;
			while (list->store_her[i])
			{
				tmp->store_her[i] = list->store_her[i];
				i++;
			}
			tmp->next = NULL;
			if (prev)
				prev->next = tmp;
			else
				head = tmp;
			prev = tmp;
			list = list->next;
		}
	}
	return (head);
}

void	close_free_wait(int *pids, int **pipefd, int num_cmd,
		t_command *tmp_cmd)
{
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
			exit(EXIT_FAILURE);
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
	free(tmp_cmd);
}

void	handle_pipe(t_command *list, t_envarment *var)
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
	tmp_cmd = get_list_command(list);

				
	pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
	heredoc_fd = -1;
	i = 0;
	
	if (!pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < num_cmd)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
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
			if (built_in_exist(tmp_cmd))
			{
				built_in(var, tmp_cmd);
				exit(EXIT_SUCCESS);
			}
			
			if (test_redir_here_doc(tmp_cmd))
			{
				hundle_redirections(tmp_cmd);
			}
			
			if(tmp_cmd->store_her[0]  != NULL)
			{
				heredoc_fd = hundle_file_herdoc(tmp_cmd);
				dup2(heredoc_fd, STDIN_FILENO);
				close(heredoc_fd);
			}
			
			ptr = path_command(tmp_cmd->content, arr_env);
			if (!ptr)
				exit(EXIT_FAILURE);
			execve(ptr, tmp_cmd->arg, arr_env);
			perror("execve failed");
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
