/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:51:59 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/27 11:04:17 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_command **lst, void (*del)(void*))
{
	t_command	*head;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		head = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = head;
	}
}
