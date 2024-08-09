/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/09 13:22:17 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_doc(t_command **new_node)
{
	(*new_node)->doc->dir_in = 0;
	(*new_node)->doc->dir_out = 0;
	(*new_node)->doc->rdir = 0;
	(*new_node)->doc->doc_here = 0;
	(*new_node)->doc->store = NULL;
}

void	ft_check_doc(t_command **new_node, t_splitor *tmp_x)
{
	t_splitor	*tmp;

	// int			i;
	tmp = tmp_x;
	// i = 0;
	(*new_node)->doc = malloc(sizeof(t_redirect));
	ft_set_doc(new_node);
	while (tmp != NULL)
	{
		if (tmp->type != '|' && ft_condition(tmp) && tmp->state == G)
		{
			if (tmp->type == '<')
				(*new_node)->doc->dir_in = 1;
			else if (tmp->type == '>')
				(*new_node)->doc->dir_out = 1;
			else if (tmp->type == HERE_DOC)
				(*new_node)->doc->doc_here = 1;
			else if (tmp->type == DREDIR_OUT)
				(*new_node)->doc->rdir = 1;
			(*new_node)->doc->len++;
		}
		tmp = tmp->next;
	}
	(*new_node)->doc->store = malloc(sizeof(char *) * (*new_node)->doc->len);
	tmp = tmp_x;
	// i = 0;
}
