/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:50:53 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/27 11:14:10 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_command *lst, void (*f)(void *))
{
	t_command	*node;

	if (!lst || !f)
		return ;
	node = lst;
	while (node != NULL)
	{
		f(node->str_input);
		node = node->next;
	}
}
