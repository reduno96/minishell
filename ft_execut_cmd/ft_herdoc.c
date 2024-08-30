/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/30 12:52:08 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc_exist(t_command *list)
{
	t_command	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->store_her && tmp->store_her[0] != NULL)
		{
			printf("herdoc exist\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}


t_here_doc	*return_herdoc(t_command *list)
{
	t_here_doc	*her;
	int			idx;
	int			i;
	t_command	*tmp;

	tmp = list;
	her = NULL;
	idx = 0;
	while (tmp)
	{
		if (tmp->store_her != NULL)
		{
			i = 0;
			while (tmp->store_her[i])
			{
				
				add_back_node_her(&her, new_node_her(idx, i, tmp->store_her[i],
						-1, false));
				i++;
			}
		}
		if (  tmp->content != NULL && tmp->content[0] != '|')
			idx++;
		tmp = tmp->next;
	}
	return (her);
}

void	redirect_heredoc_input(char *file, int fd)
{
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd < 0)
	{
		perror("open");
		return ;
	}
	close(fd);
}
int	hundle_output_herdoc(t_here_doc *her)
{
	char	*tmp_line;
	char	*path_file;

	tmp_line = ft_strjoin(her->store, ft_itoa(her->indx));
	path_file = ft_strjoin("/tmp/herdoc", tmp_line);
	free(tmp_line);
	her->fd = open(path_file, O_RDONLY);
	if (her->fd < 0)
	{
		perror("open");
		free(path_file);
		return (0);
	}
	free(path_file);
	return (her->fd);
}

void	delet_file_her(t_here_doc *delet_her)
{
	char	*path_file;
	char	*tmp_line;

	while (delet_her)
	{
		tmp_line = ft_strjoin(delet_her->store, ft_itoa(delet_her->indx));
		path_file = ft_strjoin("/tmp/herdoc", tmp_line);
		if (unlink(path_file) == -1)
		{
			perror("unlink");
		}
		free(tmp_line);
		free(path_file);
		delet_her = delet_her->next;
	}
}
void	create_files(t_here_doc *her)
{
	t_here_doc	*tmp;
	char		*path_file;
	char		*tmp_line;

	tmp = her;
	while (tmp)
	{
		tmp_line = ft_strjoin(tmp->store, ft_itoa(tmp->indx));
		path_file = ft_strjoin("/tmp/herdoc", tmp_line);
		free(tmp_line);
		redirect_heredoc_input(path_file, tmp->fd);
		free(path_file);
		tmp = tmp->next;
	}
}

void	write_in_file(t_here_doc *tmp, char *line)
{
	char	*tmp_line;
	char	*path_file;

	tmp_line = ft_strjoin(tmp->store, ft_itoa(tmp->indx));
	path_file = ft_strjoin("/tmp/herdoc", tmp_line);
	free(tmp_line);
	tmp->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp->fd < 0)
	{
		perror("open");
		return ;
	}
	ft_putstr_fd(line, tmp->fd);
	write(tmp->fd, "\n", 1);
	close(tmp->fd);
	// tmp = tmp->next;
}

int	count_herdoc(t_here_doc *her)
{
	int	i;

	i = 0;
	while (her)
	{
		i++;
		her = her->next;
	}
	return (i);
}
int	handle_here_doc(t_command *tmp, char **env)
{
	int			i;
	int			count;
	t_here_doc	*her;
	char		*line;
	int			fdk;

	t_here_doc	*delet_her;
	(void)env;
	i = 0;
	her = return_herdoc(tmp);
	count = count_herdoc(her);
	// printf("*/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	// t_here_doc	*tmp_her;
	// tmp_her = her;
	// while (tmp_her != NULL)
	// {
	// 	printf("her->file = %s et indx = %d et i = %d   et fd = %d \n",
	// 		tmp_her->store, tmp_her->indx_cmd, tmp_her->indx, tmp_her->fd);
	// 	tmp_her = tmp_her->next;
	// }
	// printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	create_files(her);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, her->store) == 0)
		{
			i++;
			if (i == count || her->next == NULL)
			{
				free(line);
				break ;
			}
			her = her->next;
		}
		else
		{
			write_in_file(her, line);
		}
		free(line);
	}
	fdk = hundle_output_herdoc(her);
	delet_her = return_herdoc(tmp);
	delet_file_her(delet_her);
	return (fdk);
}
