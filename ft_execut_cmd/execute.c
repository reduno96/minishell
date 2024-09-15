/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/15 18:11:26 by rel-mora         ###   ########.fr       */
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
		(ft_cd(list, list->ar_env));
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

void	ft_exute(t_envarment **var, t_command *cmd)
{
	t_command	*list;
	int			pid;

	list = cmd;
	list->ar_env = NULL;
	list->ar_env = array_env(var);
	if (run_herdoc_built(var, cmd) == 1)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
		run_command(list, var);
	else
	{
		parent_proc(pid);
	}
	ft_free_leaks(list, var);
}
