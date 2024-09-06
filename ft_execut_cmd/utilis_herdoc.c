/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/06 09:24:08 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



// t_here_doc	*new_node_her(int idx, int i, char *file, int fd, bool expand)
// {
// 	t_here_doc	*elem;

// 	elem = (t_here_doc *)malloc(sizeof(t_here_doc));
// 	if (!elem)
// 		return (NULL);
// 	elem->indx_cmd = idx;
// 	elem->indx = i;
// 	elem->store = file;
// 	elem->fd = fd;
// 	elem->is_expanded = expand;
// 	elem->next = NULL;
// 	return (elem);
// }

// void	add_back_node_her(t_here_doc **her, t_here_doc *new_her)
// {
// 	t_here_doc	*p;

// 	p = *her;
// 	if (!her || !new_her)
// 		return ;
// 	if (!(*her))
// 	{
// 		*her = new_her;
// 		return ;
// 	}
// 	while (p->next)
// 	{
// 		p = p->next;
// 	}
// 	p->next = new_her;
// }





t_here_doc	*new_node_her(char *file, int fd  , int x, int is_expand)
{
	t_here_doc	*elem;
	char	*tmp_line;
	char 	*path_file;

	elem = (t_here_doc *)malloc(sizeof(t_here_doc));
	if (!elem)
		return (NULL);

	tmp_line = ft_strjoin(file, ft_itoa(x));
	path_file = ft_strjoin("/tmp/herdoc", tmp_line);
	free(tmp_line);

	elem->store = file;
	elem->fd = fd;
	elem->idx = x;
	elem->expad = is_expand;
	elem->heredoc_file =  ft_strdup(path_file);
	elem->next = NULL;
	return (elem);
}

void	add_back_node_her(t_here_doc **her, t_here_doc *new_her)
{
	t_here_doc	*p;

	p = *her;
	if (!her || !new_her)
		return ;
	if (!(*her))
	{
		*her = new_her;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new_her;
}
