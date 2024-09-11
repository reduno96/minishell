/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:29:09 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/11 09:44:38 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_spaces_in_count__2(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
	ft_skip_spaces(tmp_x);
	while ((*tmp_x) != NULL && ((*tmp_x)->type == -1 || (*tmp_x)->type == '$'
			|| ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\'')
				|| (((*tmp_x)->type == 32 && (*tmp_x)->state != G))))
		(*tmp_x) = (*tmp_x)->next;
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_spaces(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && (*tmp_x)->type == ' ')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_spaces_in_count(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
	while ((*tmp_x) != NULL && (*tmp_x)->state != G)
		(*tmp_x) = (*tmp_x)->next;
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_quote(t_splitor **tmp_x, int *i, t_command **new_node)
{
	(*tmp_x) = (*tmp_x)->next;
	if (((*tmp_x) != NULL && (*tmp_x)->state == G) && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		(*i)++;
		(*new_node)->arg[*i] = ft_strdup("");
		(*new_node)->next = NULL;
	}
}

void	ft_skip_not_word(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '<' || (*tmp_x)->type == '>'
			|| (*tmp_x)->type == DREDIR_OUT || (*tmp_x)->type == HERE_DOC))
	{
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		ft_skip_spaces_in_count__2(tmp_x);
	}
}
