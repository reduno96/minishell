/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_synx_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:13:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/08 11:13:50 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envarment	*new_node(void *var, void *data)
{
	t_envarment	*elem;

	elem = (t_envarment *)malloc(sizeof(t_envarment));
	if (!elem)
		return (NULL);
	elem->var = var;
	elem->data = data;
	elem->next = NULL;
	return (elem);
}

void	add_back_node(t_envarment **lst, t_envarment *new)
{
	t_envarment	*p;

	p = *lst;
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new;
}

t_envarment	*ft_stock_envarment(char **env)
{
	t_envarment	*var;
	char		**list;
	int			i;
	t_envarment	*elem;

	var = NULL;
	i = 0;
	while (env[i])
	{
		list = ft_split(env[i], '=');
		elem = new_node(list[0], list[1]);
		add_back_node(&var, elem);
		free(list);
		i++;
	}
	return (var);
}
