/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/14 17:28:00 by bouhammo         ###   ########.fr       */
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



// void	ft_access(char *ptr, char **str)
// {
// 	// printf("**************************             %s\n", *str);
// 	if ( ptr == NULL || str == NULL || *str == NULL )
// 		return ;
// 	if (access(ptr, F_OK) == -1)
// 	{
// 		ft_putstr_fd("1command not found\n", 2);
// 		if (ptr != str[0])
// 			free(ptr);
// 		g_exit_status = 127;
// 		exit(127);
// 	}
// 	if (is_directory(ptr))
// 	{
// 		ft_putstr_fd(ptr, 2);
// 		ft_putstr_fd(": is a directory\n", 2);
// 		g_exit_status = 126;
// 		exit(126);
// 	}
// 	if (ft_strncmp(ptr, "./", 2) == 0)
// 	{
// 		if (access(ptr, X_OK) == -1)
// 		{
// 			ft_putstr_fd("command not found\n", 2);
// 			if (ptr != str[0])
// 				free(ptr);
// 			g_exit_status = 127;
// 			exit(127);
// 		}
// 	}
// }

int is_directory(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode)) {
        return 1;
    }
    return 0;
}

void ft_access(char *ptr, char **str, t_command *list) {
    (void)list;

    if (ptr == NULL || str == NULL || *str == NULL)
        return;

    struct stat path_stat;

	if (access(ptr, F_OK) == -1 && ft_strncmp(ptr,"./",2) == 0)
	{
        ft_putstr_fd(ptr, 2);
        ft_putstr_fd(": command not found\n", 2);
        if (ptr != str[0])
            free(ptr);
        g_exit_status = 127;
        exit(127);
    }
    else if (access(ptr, X_OK) == -1  )//&& stat(ptr, &path_stat) != -1 && S_ISDIR(path_stat.st_mode) !=1)
	{
        ft_putstr_fd(ptr, 2);
        ft_putstr_fd(": Permission denied\n", 2);
        if (ptr != str[0])
            free(ptr);
        g_exit_status = 126;
        exit(126);
    }
    else  if (stat(ptr, &path_stat) == -1)
	{
        ft_putstr_fd(ptr, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        if (ptr != str[0])
            free(ptr);
        g_exit_status = 127;
        exit(127);
    }
    else if (S_ISDIR(path_stat.st_mode) ==1)
	{
        if (ft_strchr(ptr, '/')) { 
            ft_putstr_fd(ptr, 2);
            ft_putstr_fd(": is a directory\n", 2);
            g_exit_status = 126;
        }
		else
		{
            ft_putstr_fd(ptr, 2);
            ft_putstr_fd(": command not found\n", 2); 
            g_exit_status = 127;
        }
        if (ptr != str[0])
            free(ptr);
        exit(g_exit_status);
    }
	else
		return ;
}




// void	ft_access(char *ptr, char **str)
// {
// 	// printf("**************************             %s\n", *str);
// 	if ( ptr == NULL || str == NULL || *str == NULL )
// 		return ;
// 	printf("---------------->>>>>>> %s\n", ptr);
// 	if (access(ptr, F_OK) == -1)
// 	{
// 		ft_putstr_fd("1command not found\n", 2);
// 		if (ptr != str[0])
// 			free(ptr);
// 		g_exit_status = 127;
// 		exit(127);
// 	}
// 	if (is_directory(ptr))
// 	{
// 		ft_putstr_fd(ptr, 2);
// 		ft_putstr_fd(": is a directory\n", 2);
// 		g_exit_status = 126;
// 		exit(126);
// 	}
// 	if (ft_strncmp(ptr, "./", 2) == 0)
// 	{
// 		if (access(ptr, X_OK) == -1)
// 		{
// 			ft_putstr_fd("command not found\n", 2);
// 			if (ptr != str[0])
// 				free(ptr);
// 			g_exit_status = 127;
// 			exit(127);
// 		}
// 	}
// }

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
	ft_access(ptr, new, list);


	if (execve(ptr, new, list->ar_env) == -1)
	{
		perror("execve");
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
	}
	else if (pipe_exist(list) == 1)
	{
		handle_pipe(list, var);
		exit(g_exit_status);
	}
	else
	{
		if (test_redir_here_doc(list) == 1)
		{
			hundle_redirections(list);
			built_in(var, list);
		}
		if (built_in_exist(list) == 0)
			execution_cmd(list, list->arg);
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
int 	run_herdoc_built(t_envarment **var, t_command *cmd)
{
	t_command	*list;

	list = cmd;
	if (list == NULL)
		return -1;

	if (herdoc_exist(list) == 1)
	{
		handle_here_doc(var, list);
	}
	if (built_in_exist(list) == 1 && pipe_exist(list) == 0
		&& herdoc_exist(list) == 0 && test_redir_here_doc(list) == 0)
	{
		if (test_redir_here_doc(list) == 1)
			hundle_redirections(list);
		built_in(var, list);
		return 1;
	}
	return 0;
}

void	ft_exute(t_envarment **var, t_command *cmd)
{
	t_command	*list;
	int			status;
	int			pid;

	list = cmd;
	list->ar_env = NULL;
	list->ar_env = array_env(var);
	if (run_herdoc_built(var, cmd) == 1)
		return;
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
	ft_free_leaks(list, var);
}
