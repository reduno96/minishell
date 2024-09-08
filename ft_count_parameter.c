/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_parameter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:51:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/06 16:54:10 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_d_s(t_splitor **tmp, int *count)
{
	while ((*tmp) != NULL && ((*tmp)->state == D || (*tmp)->state == S))
	{
		if ((*tmp) != NULL)
			(*tmp) = (*tmp)->next;
		while ((*tmp) != NULL && (*tmp)->state == G && ((*tmp)->type == '\"'
				|| (*tmp)->type == '\''))
		{
			if ((*tmp) != NULL)
				(*tmp) = (*tmp)->next;
		}
		if ((*tmp) != NULL)
			(*tmp) = (*tmp)->next;
	}
	(*count)++;
}

void	ft_count_general(t_splitor **tmp, int *count)
{
	if ((*tmp) != NULL)
		(*tmp) = (*tmp)->next;
	while ((*tmp) != NULL && (*tmp)->state == G && ((*tmp)->type == '\"'
			|| (*tmp)->type == '\''))
	{
		while (((*tmp) != NULL && (*tmp)->state == G) && ((*tmp)->type == '\"'
				|| (*tmp)->type == '\''))
			(*tmp) = (*tmp)->next;
		if ((*tmp) != NULL)
			(*tmp) = (*tmp)->next;
	}
	(*count)++;
}

void	ft_count_parameters(t_splitor *tmp_x, int *count)
{
	t_splitor	*tmp;

	tmp = tmp_x;
	if (tmp != NULL && tmp->type == '|' && tmp->state == G)
		(*count)++;
	else if (tmp != NULL)
	{
		if ((tmp != NULL && tmp->next != NULL) && ((tmp->type == '\''
					&& tmp->next->type == '\'') || (tmp->type == '\"'
					&& tmp->next->type == '\"')))
		{
			(*count)++;
			tmp = tmp->next;
		}
		while (tmp != NULL && !(tmp->type == '|' && tmp->state == G))
		{
			if (tmp->type == '<' || tmp->type == '>' || tmp->type == DREDIR_OUT
				|| tmp->type == HERE_DOC)
			{
				tmp = tmp->next;
				ft_skip_spaces(&tmp);
				if ((tmp != NULL && tmp->next != NULL) && ((tmp->type == '\''
							&& tmp->next->type == '\'') || (tmp->type == '\"'
							&& tmp->next->type == '\"')))
					tmp = tmp->next;
				else
					ft_skip_spaces_in_count(&tmp);
				if (tmp != NULL)
					tmp = tmp->next;
			}
			if ((tmp != NULL && tmp->next != NULL) && ((tmp->type == '\''
						&& tmp->next->type == '\'') || (tmp->type == '\"'
						&& tmp->next->type == '\"')))
			{
				(*count)++;
				tmp = tmp->next;
			}
			else if ((tmp) != NULL && (tmp)->state == G && ((tmp)->type != '\"'
					&& (tmp)->type != '\'') && (tmp)->type != ' ')
			{
				ft_count_general(&tmp, count);
			}
			else if (tmp != NULL && (tmp->state == D || tmp->state == S))
			{
				ft_count_d_s(&tmp, count);
			}
			else if (tmp != NULL && tmp->type != '|')
			{
				tmp = tmp->next;
			}
		}
	}
}
