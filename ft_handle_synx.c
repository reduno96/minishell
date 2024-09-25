/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_synx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:47:51 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/25 16:58:23 by bouhammo         ###   ########.fr       */
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

int	redirection(t_splitor *start)
{
	if ((start)->type == '<' || (start)->type == '>'
		|| (start)->type == DREDIR_OUT || (start)->type == HERE_DOC)
		return (1);
	return (0);
}

int	quotes(t_splitor *start)
{
	if ((start)->type == '\"' || (start)->type == '\'')
		return (1);
	return (0);
}

void	ft_next_check(t_splitor **start)
{
	if (((*start) != NULL) && ft_condition(*start) && (*start)->state != G)
		while (((*start) != NULL) && (ft_condition(*start)
				&& (*start)->state != G))
			(*start) = (*start)->next;
	else if (((*start) != NULL) && !ft_condition(*start) && (*start)->state != G)
		while (((*start) != NULL) && !ft_condition(*start)
			&& (*start)->state != G)
			(*start) = (*start)->next;
	else if (((*start) != NULL) && (*start)->state == G)
		(*start) = (*start)->next;
}

int	ft_check_between(t_splitor **start)
{
	while ((*start) != NULL)
	{
		ft_skip_spaces(&(*start));
		if (((*start) != NULL) && redirection((*start)) && ((*start)->state == G))
		{
			(*start) = (*start)->next;
			ft_skip_spaces(&(*start));
			if ((*start) == NULL || ((redirection(*start)
						|| (*start)->type == '|') && (*start)->state == G))
			{
				return (1);
				printf("1\n");
			}
		}
		else if (((*start) != NULL) && (*start)->type == '|' && ((*start)->state == G))
		{
			(*start) = (*start)->next;
			ft_skip_spaces(&(*start));
			if ((*start) == NULL || (((*start)->type == '|')
					&& (*start)->state == G))
				return (1);
		}
		else
			ft_next_check(start);
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
	ft_skip_spaces(&start);
	if (start != NULL &&  ( start->type == '|' || ((start->type != ' ' && start->type != -1
				&& start->type != '$') && start->next == NULL)
		|| ((start->type == '\'' || start->type == '\"')
				&& start->next == NULL)))
		return (1);
	if (ft_check_between(&start))
		return (1);
	start = *x;
	end = ft_lstlast(start);
	if (end->type == '|')
		return (1);
	return (0);
}
