/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:25:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/20 19:13:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_command(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_command(*lst);
		last->next = new;
	}
}

t_command	*ft_last_command(t_command *lst)
{
	t_command	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_her_doc(t_command **new_node)
{
	t_redirect	*tmp;
	int			i;

	i = 0;
	tmp = (*new_node)->doc;
	while (tmp != NULL)
	{
		if (tmp->type == HERE_DOC)
			(*new_node)->len++;
		tmp = tmp->next;
	}
	(*new_node)->store_her = malloc(sizeof(char *) * (*new_node)->len + 1);
	tmp = (*new_node)->doc;
	while (tmp != NULL)
	{
		if (tmp->type == HERE_DOC)
		{
			(*new_node)->store_her[i] = ft_strdup(tmp->store);
			i++;
		}
		tmp = tmp->next;
	}
	(*new_node)->store_her[i] = NULL;
}
t_command	*ft_new_command(int count, t_splitor **tmp_x)
{
	t_command	*new_node;
	int			i;

	i = 0;
	new_node = malloc(sizeof(t_command));
	new_node->arg = malloc(sizeof(char *) * (count + 1));
	new_node->len = 0;
	new_node->is_pipe = 0;
	if (((*tmp_x) != NULL && ((*tmp_x)->type == '|' && (*tmp_x)->state == G)))
	{
		new_node->arg[i] = ft_strdup((*tmp_x)->in);
		i++;
		new_node->arg[i] = NULL;
		new_node->is_pipe = 1;
		new_node->next = NULL;
		(*tmp_x) = (*tmp_x)->next;
	}
	else if ((*tmp_x) != NULL)
		ft_not_pipe(&new_node, &i, tmp_x);
	new_node->content = new_node->arg[0];
	new_node->doc = NULL;
	ft_check_doc(&new_node);
	ft_her_doc(&new_node);
	return (new_node);
}
