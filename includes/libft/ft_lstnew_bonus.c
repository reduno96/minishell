/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 21:18:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/27 19:51:49 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_command *ft_lstnew(void *content, int len, t_token type, t_state state)
{
	t_command *new_node;

	new_node = malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->str_input = content;
	new_node->len = len;
	new_node->type = type;
	new_node->state = state;
	new_node->next = NULL;
	return (new_node);
}
