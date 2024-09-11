/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/11 20:02:41 by bouhammo         ###   ########.fr       */
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

void	built_in(t_envarment **var, t_command *list)
{
	
	if (list == NULL)
		return ;
		if (ft_strcmp(list->content, "exit") == 0)
			(ft_exit(var, list));
		if (ft_strcmp(list->content, "cd") == 0)
			(ft_cd(list ));
		if (ft_strcmp(list->content, "pwd") == 0)
			(ft_pwd(list));
		if (ft_strcmp(list->content , "export") == 0)
		{
			printf("[]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]       \n");	
			(ft_export(var, list ));
		}
		if (ft_strcmp(list->content , "unset") == 0)
			(ft_unset(var, list));
		if (ft_strcmp(list->content , "env") == 0)
			(ft_env(var));
		if (ft_strcmp(list->content , "echo") == 0)
		{
			(ft_echo(list ));
		}
}

void	execution_cmd(t_command *list, char **new)
{
	char	*ptr;
printf("***********************************  %d \n", getpid());
	if (list == NULL || new == NULL || new[0] == NULL || list->arg == NULL)
		return ;
	if (new[0][0] == '/')
		ptr = new[0];
	else
	{
		ptr = path_command(new[0], list->ar_env);
		printf("OK\n");
		g_exit_status = 1;
	}
	if (!ptr)
	{
		g_exit_status = 127;
		printf("get+status           %d\n", g_exit_status);
		ft_putstr_fd("1 command not found\n", 2);
		exit(127);
	}
	if (access(ptr, X_OK) == -1)
	{
		g_exit_status = 126;
		printf("get+status           %d\n", g_exit_status);
		ft_putstr_fd(" 2 command not found \n", 2);
		free(ptr);
		exit(126);
	}
	if (execve(ptr, new, list->ar_env) == -1)
	{
		perror("execve ");
		free(ptr);
		g_exit_status = 127;
		exit(127);
	}
	
}


int	built_in_exist(t_command *list)
{
	if(list == NULL)
		return 0;
	if (ft_strcmp(list->content, "exit") == 0)
		return (1);
	if (ft_strcmp(list->content, "cd") == 0)
		return (1);
	if (ft_strcmp(list->content , "pwd") == 0)
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


void		run_command(t_command *list ,t_envarment **var ,char **env) 
{
	int			heredoc_fd;
	(void)env;

	heredoc_fd = -1;
	if (herdoc_exist(list) == 1 && pipe_exist(list) == 0 )
	{
		heredoc_fd = hundle_file_herdoc(list);
		if (heredoc_fd != -1)
		{
			dup2(heredoc_fd, STDIN_FILENO);
			close(heredoc_fd);
		}
		hundle_redirections(list);
		execution_cmd(list, list->arg);

	}
	else  if(pipe_exist(list) == 1 )
	{
		handle_pipe(list, var);
	}
	else
	{
		if (test_redir_here_doc(list))
		{
			hundle_redirections(list);
			built_in(var, list);
		}
		if (built_in_exist(list) == 0)
			execution_cmd(list, list->arg);

	}
	// g_exit_status = 126;
	exit(EXIT_SUCCESS);
}

	
void 		ft_free_leaks(t_command  *list , t_envarment **var)
{
	int 	i;
	(void)var;
	i = 0;
	while (list->ar_env[i])
	{
		free(list->ar_env[i]);
		i++;
	}
	free(list->ar_env);
	
}
void	ft_exute(t_envarment **var, t_command *cmd, char **env)
{
	t_command	*list;
	int			status;
	int			pid;

	list = cmd;
	if (list == NULL)
		return ;
	list->ar_env = array_env(var);
	if (herdoc_exist(list) == 1)
	{
		handle_here_doc(list, env);
	}
	if (built_in_exist(list) == 1 && pipe_exist(list) == 0 && herdoc_exist(list) == 0 && test_redir_here_doc(list) == 0)
	{
		if (test_redir_here_doc(list) == 1)
			hundle_redirections(list);
		built_in(var, list);
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
		run_command(list ,var , env) ;
	}
	else
	{
		printf("[][][][][][][][[[][][][[][]]]]\n");
		printf("=======================   1 | %d \n", g_exit_status);
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			g_exit_status = status;
			exit(status);
		}
	}
	printf("=======================   0 |  %d \n", g_exit_status);
	ft_free_leaks(list , var);
}
