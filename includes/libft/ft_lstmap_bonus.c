/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:50:49 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/29 16:50:19 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_splitor	*ft_lstmap(t_splitor *lst, void *(*f)(void *), void (*del)(void *))
{
	t_splitor	*new_lst;
	t_splitor	*temp_lst;
	t_splitor	*new_node;
	void		*new_content;

	if (!lst || !f || !del)
		return (NULL);
	temp_lst = lst;
	new_lst = NULL;
	while (temp_lst != NULL)
	{
		new_content = f(temp_lst->str_input);
		new_node = ft_lstnew(new_content, 100, WORD, GENERAL);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_add(&new_lst, new_node);
		temp_lst = temp_lst->next;
	}
	return (new_lst);
}
