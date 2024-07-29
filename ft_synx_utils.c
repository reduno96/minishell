/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_synx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:13:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/29 09:47:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_node(t_environment **lst, t_environment *new)
{
	t_environment	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_node(*lst);
		last->next = new;
	}
}

t_environment	*ft_new_node(void *content)
{
	t_environment	*new_node;

	new_node = malloc(sizeof(t_environment));
	if (!new_node)
		return (NULL);
	new_node->line = content;
	new_node->next = NULL;
	return (new_node);
}

t_environment	*ft_last_node(t_environment *lst)
{
	t_environment	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}
