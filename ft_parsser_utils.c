/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 21:25:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/17 11:34:22 by rel-mora         ###   ########.fr       */
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

t_command	*ft_new_command(int count, t_splitor **tmp_x, t_envarment *my_env)
{
	t_command	*new_node;
	int			i;

	i = 0;
	new_node = malloc(sizeof(t_command));
	new_node->arg = malloc(sizeof(char *) * (count + 1));
	new_node->content = NULL;
	new_node->arg[0] = NULL;
	new_node->len = 0;
	new_node->is_pipe = 0;
	new_node->doc = NULL;
	new_node->her = NULL;
	if (((*tmp_x) != NULL && ((*tmp_x)->type == '|' && (*tmp_x)->state == G)))
	{
		new_node->arg[i] = ft_strdup((*tmp_x)->in);
		i++;
		new_node->arg[i] = NULL;
		new_node->is_pipe = 1;
		(*tmp_x) = (*tmp_x)->next;
	}
	else if ((*tmp_x) != NULL)
		ft_not_pipe(&new_node, &i, tmp_x, my_env);
	new_node->content = new_node->arg[0];
	new_node->next = NULL;
	return (new_node);
}
