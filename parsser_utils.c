/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsser_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:07:29 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/31 14:22:55 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_commad(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_commad(*lst);
		last->next = new;
	}
}

t_command	*ft_new_command(t_info *arg)
{
	t_command	*new_node;

	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->content = arg->s;
	new_node->r_in = arg->i;
	new_node->r_out = arg->o;
	new_node->h_doc = arg->h;
	new_node->dr_out = arg->d;
	new_node->next = NULL;
	return (new_node);
}

t_command	*ft_last_commad(t_command *lst)
{
	t_command *last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}