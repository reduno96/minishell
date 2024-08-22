/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/22 12:55:22 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_here_doc	*new_node_her(int idx, int i, char *file, int fd, bool expand)
{
	t_here_doc	*elem;

	elem = (t_here_doc *)malloc(sizeof(t_here_doc));
	if (!elem)
		return (NULL);
	elem->indx_cmd = idx;
	elem->indx = i, elem->store = file;
	elem->fd = fd;
	elem->is_expanded = expand;
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
