/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/07 07:35:09 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_doc(t_command **new_node)
{
	(*new_node)->doc->dir_in = NULL;
	(*new_node)->doc->dir_out = NULL;
	(*new_node)->doc->rdir = NULL;
	(*new_node)->doc->doc_here = NULL;
}

void	ft_check_doc(t_command **new_node)
{
	int	i;

	i = 0;
	(*new_node)->doc = malloc(sizeof(t_redirect));
	ft_set_doc(new_node);
	while (((*new_node)->arg) && (*new_node)->arg[i] != NULL)
	{
		if (ft_strchr((*new_node)->arg[i], '<'))
			(*new_node)->doc->dir_in = ft_strdup((*new_node)->arg[i]);
		else if (ft_strchr((*new_node)->arg[i], '>'))
			(*new_node)->doc->dir_out = ft_strdup((*new_node)->arg[i]);
		else if (ft_search((*new_node)->arg[i], "<<"))
			(*new_node)->doc->doc_here = ft_strdup((*new_node)->arg[i]);
		else if (ft_search((*new_node)->arg[i], ">>"))
			(*new_node)->doc->rdir = ft_strdup((*new_node)->arg[i]);
		i++;
	}
}
