/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:33:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/15 10:32:35 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void		hundle_redir_out(char 	*file)
{
	int fd;
	fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	int d = dup2(fd, STDOUT_FILENO) ;
	if (d <  0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}
void		hundle_redir_in(char 	*file)
{
	int fd;
	fd = open(file, O_RDONLY  , 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	int d = dup2(fd, STDIN_FILENO) ;
	if (d <  0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}
void		hundle_dredir_out(char *file)
{
	int fd = open(file, O_RDWR | O_CREAT | O_APPEND , 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	int d = dup2(fd, STDOUT_FILENO) ;
	if (d <  0)
	{
		perror("dup2");
		exit(1);
	}
}
