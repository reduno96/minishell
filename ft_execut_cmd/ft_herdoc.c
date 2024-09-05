/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/05 15:15:28 by rel-mora         ###   ########.fr       */
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
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_here_doc	*return_herdoc(t_command *list)
{
	t_here_doc	*her;
	// int			idx;
	int			i;
	int 		j;
	t_command	*tmp;

	tmp = list;
	her = NULL;
	// idx = 0;
	j = 0;
	while (tmp)
	{
			i = 0;
		if (tmp->store_her != NULL)
		{
			while (tmp->store_her[i])
			{
				add_back_node_her(&her, new_node_her( tmp->store_her[i], -1 ,j, 1));
				i++;
				j++;
			}
		}
		tmp = tmp->next;
	}
	return (her);
}




// void	delet_file_her(t_here_doc *delet_her)
// {
// 	char	*path_file;
// 	char	*tmp_line;

// 	while (delet_her)
// 	{
// 		tmp_line = ft_strjoin(delet_her->store, ft_itoa(delet_her->indx));
// 		path_file = ft_strjoin("/tmp/herdoc", tmp_line);
// 		if (unlink(path_file) == -1)
// 		{
// 			perror("unlink");
// 		}
// 		free(tmp_line);
// 		free(path_file);
// 		delet_her = delet_her->next;
// 	}
// }



void	write_in_file(t_here_doc *tmp, char *line)
{
	char	*tmp_line;
	// char 	*path_file;

	tmp_line = ft_strjoin(tmp->store, ft_itoa(tmp->idx));
	// path_file = ft_strjoin("/tmp/herdoc", tmp_line);
	free(tmp_line);

	tmp->fd = open(tmp->heredoc_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp->fd < 0)
	{
		perror("open");
		return ;
	}

	ft_putstr_fd(line, tmp->fd);
	write(tmp->fd, "\n", 1);
	close(tmp->fd);
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

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	exit(0);
// }


void	handle_here_doc(t_command *tmp, char **env)
{
	int			i;
	int			count;
	t_here_doc	*her;
	char		*line;

	(void)env;
	i = 0;
	her = return_herdoc(tmp);

	// t_here_doc	 *ttmp  = NULL;
	// ttmp = her;

	count = count_herdoc(her);
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
			write_in_file(her, line);
		free(line);
	}


// while (ttmp)
// {
// 	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++     \n");
// 		printf("her->store = %s\n", ttmp->store);
// 		printf("her->fd = %d\n", ttmp->fd);
// 		printf("her->file = %s\n", ttmp->heredoc_file);
// 		printf("her->indx = %d\n", ttmp->idx);
// 	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++     \n");
// 	ttmp = ttmp->next;
// }
}
