/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_synx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:47:51 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/02 19:08:25 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_condition(t_splitor *start)
{
	if ((start->type != ' ' && start->type != -1 && start->type != '$'
			&& start->type != '\'' && start->type != '\"'
			&& start->type != HERE_DOC))
		return (1);
	return (0);
}

int	ft_check_between(t_splitor **start)
{
	while ((*start) != NULL)
	{
		if ((*start)->type == '|' || (*start)->type == HERE_DOC
			|| (ft_condition(*start) && ((*start)->state == G)))
		{
			if ((*start) != NULL)
				(*start) = (*start)->next;
			ft_skip_spaces(&(*start));
			if ((*start) == NULL ||  ((*start)->type == '|' && (ft_condition(*start)) && (*start)->state == G))
			{
				// printf("Hi i'm in ft_check_between\n");
				return (1);
			}
		}
		else if (ft_condition(*start) && (*start)->state != G)
			while (((*start) != NULL) && (ft_condition(*start)
					&& (*start)->state != G))
				(*start) = (*start)->next;
		else if (!ft_condition(*start) && (*start)->state != G)
			while (((*start) != NULL) && !ft_condition(*start)
				&& (*start)->state != G)
				(*start) = (*start)->next;
		else if (((*start) != NULL) && (*start)->state == G)
			(*start) = (*start)->next;
	}
	return (0);
}

int	ft_handler_syn_error(t_splitor **x)
{
	t_splitor	*start;
	t_splitor	*end;

	if (!(*x))
		return (0);
	start = *x;
	if (start->type == '|' || ((start->type != ' ' && start->type != -1
				&& start->type != '$') && start->next == NULL)
		|| ((start->type == '\'' || start->type == '\"')
				&& start->next == NULL))
	{
		// printf("Hi i'm in first condion \n");
		return (1);
	}
	if (ft_check_between(&start))
	{
		// printf("Hi i'm in second condion \n");
		return (1);
	}
	start = *x;
	end = ft_lstlast(start);
	if (end->type == '|')
		return (1);
	return (0);
}
