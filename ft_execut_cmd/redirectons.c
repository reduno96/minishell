/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:33:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/02 19:00:15 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hundle_redir_out(char *file)
{
	if (file == NULL)
	{
		printf("ambiguous redirect\n");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}

	int	fd;

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
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	hundle_redir_in(char *file)
{
	if (file == NULL)
	{
		printf("ambiguous redirect\n");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	int	fd;

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
	if (file == NULL)
	{
		printf("ambiguous redirect\n");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}

	int	fd;

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
