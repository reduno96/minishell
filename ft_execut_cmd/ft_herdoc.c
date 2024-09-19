/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/19 13:13:36 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hundle_chil_pro(t_here_doc *tmp_her, t_envarment **var)
{
	char	*line;

	signal(SIGINT, sig_herdoc);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			exit(EXIT_SUCCESS);
		if (ft_strcmp(line, tmp_her->store) == 0)
			exit(EXIT_SUCCESS);
		else
			write_in_file(tmp_her, line, var);
	}
}

int	handle_fork(t_here_doc *tmp_her, t_envarment **var)
{
	int		pid;
	int		status;
	void	(*old_sigint_handler)(int);

	status = -1;
	old_sigint_handler = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		signal(SIGINT, old_sigint_handler);
		return (0);
	}
	if (pid == 0)
	{
		hundle_chil_pro(tmp_her, var);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			g_exit_status = status;
	}
	return (status);
}

int	ft_cmp_delimeter(t_command *tmp_cmd, t_envarment **var)
{
	t_here_doc	*tmp_her;
	int			status;

	status = -1;
	tmp_her = tmp_cmd->her;
	while (tmp_cmd != NULL && tmp_her != NULL)
	{
		status = handle_fork(tmp_her, var);
		if (status == 256)
			return (status);
		tmp_her = tmp_her->next;
	}
	return (status);
}

void	create_files(t_command *cmd, char *itoa)
{
	t_command	*tmp;
	t_here_doc	*tmp_her;
	char		*tmp_line;
	char		*path_file;

	if (cmd == NULL)
		return ;
	tmp = cmd;
	while (tmp != NULL)
	{
		tmp_her = tmp->her;
		while (tmp != NULL && tmp_her != NULL)
		{
			itoa = ft_itoa(tmp_her->idx);
			tmp_line = ft_strjoin_1(tmp_her->store, itoa);
			free(itoa);
			path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
			free(tmp_line);
			tmp_her->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
			free(path_file);
			close(tmp_her->fd);
			tmp_her = tmp_her->next;
		}
		tmp = tmp->next;
	}
}

void	handle_here_doc(t_envarment **var, t_command *cmd)
{
	t_command	*tmp_cmd;
	int			status;
	char		*itoa;

	itoa = NULL;
	tmp_cmd = cmd;
	if (cmd == NULL || tmp_cmd == NULL)
		return ;
	create_files(tmp_cmd, itoa);
	while (tmp_cmd != NULL)
	{
		status = ft_cmp_delimeter(tmp_cmd, var);
		if (status == 256)
			break ;
		tmp_cmd = tmp_cmd->next;
	}
}
