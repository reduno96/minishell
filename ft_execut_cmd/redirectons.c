/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:33:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/05 10:24:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int hundle_file_herdoc(t_command *list)
{
    int fd;
    char *file;
    char *file_name;
    t_command *tmp;
    static  int j;

    tmp = list;
    j = 0;

    while (tmp->store_her[j])
	{
		// printf("jjjjjjjjjjjjjjjj     = %d\n", j);	
        j++;
	}
    file_name = ft_strjoin("/tmp/herdoc", tmp->store_her[j-1]);
    file = ft_strjoin(file_name, ft_itoa(j-1));
    fd = open(file, O_RDONLY, 0644);  
    

    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) < 0)  
    {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
    free(file_name);

    return fd;
}

	

void	hundle_redir_out(char *file)
{
	int	fd;

	if (file == NULL)
	{
		printf("*ambiguous redirect\n");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
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
		printf("ambiguous redirect\n");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}

void	hundle_dredir_out(char *file)
{
	int	fd;

	if (file == NULL)
	{
		printf("ambiguous redirect\n");
		g_exit_status = 1;
		exit(EXIT_FAILURE);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
