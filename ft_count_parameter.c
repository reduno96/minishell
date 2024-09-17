/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_parameter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:51:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/17 15:16:54 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_d_s(t_splitor **tmp, int *count)
{
	while ((*tmp) != NULL && ((*tmp)->state == D || (*tmp)->state == S
			|| (*tmp)->type == '\"' || (*tmp)->type == '\''))
	{
		if ((*tmp)->state == D || (*tmp)->state == S)
			(*tmp) = (*tmp)->next;
		while ((*tmp) != NULL && (*tmp)->state == G && ((*tmp)->type == '\"'
				|| (*tmp)->type == '\''))
		{
			if (((*tmp) != NULL && (*tmp)->state == G) && ((*tmp)->type == '\"'
					|| (*tmp)->type == '\''))
				(*tmp) = (*tmp)->next;
			while ((*tmp) != NULL && ((*tmp)->state == D || (*tmp)->state == S))
				(*tmp) = (*tmp)->next;
			if ((*tmp) != NULL && ((*tmp)->state == G && (*tmp)->type == -1))
				(*tmp) = (*tmp)->next;
			else if ((*tmp) != NULL && (*tmp)->type != ' ')
				(*tmp) = (*tmp)->next;
			if ((*tmp) != NULL && ((*tmp)->state == G && (*tmp)->type == -1))
				(*tmp) = (*tmp)->next;
		}
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
			if (tmp->state == G && (tmp->type == '<' || tmp->type == '>'
					|| tmp->type == DREDIR_OUT || tmp->type == HERE_DOC))
			{
				// printf("1\n");
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
				// printf("2\n");
				(*count)++;
				tmp = tmp->next;
			}
			else if ((tmp) != NULL && (tmp)->state == G && ((tmp)->type != '\"'
					&& (tmp)->type != '\'') && (tmp)->type != ' ')
			{
				// printf("3\n");
				ft_count_general(&tmp, count);
			}
			else if (tmp != NULL && (tmp->state == D || tmp->state == S))
			{
				// printf("4\n");
				ft_count_d_s(&tmp, count);
			}
			else if (tmp != NULL && tmp->type != '|')
			{
				// printf("5\n");
				tmp = tmp->next;
			}
		}
	}
}
