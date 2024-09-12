/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:33:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/12 08:07:15 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	hundle_file_herdoc(t_command *list)
{
	int			fd;
	char		*file;
	char		*file_name;
	t_command	*tmp;
	char	 *itoa;

	tmp = list;
	if (tmp->her == NULL)
		return (0);
	while (tmp->her->next)
		tmp->her = tmp->her->next;
	itoa = ft_itoa(tmp->her->idx);
	file = ft_strjoin_1(tmp->her->store, itoa);
	free(itoa);
	file_name = ft_strjoin_1("/tmp/herdoc", file);
	free(file);
	fd = open(file_name, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("open");
		g_exit_status = 0;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		g_exit_status = 0;
		exit(EXIT_FAILURE);
	}

	close(fd);
	free(file_name);
	return (fd);
}

void	hundle_redir_out(char *file)
{
	int	fd;

	if (file == NULL)
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	hundle_redir_in(char *file)
{
	int	fd;

	if (file == NULL)
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	hundle_dredir_out(char *file)
{
	int	fd;

	if (file == NULL)
	{
		ft_putstr_fd("ambiguous redirect\n", 2);
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	close(fd);
}
