/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsser_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/07 07:25:23 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skeep_space(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && (*tmp_x)->type == ' ')
		(*tmp_x) = (*tmp_x)->next;
}

int	ft_check_command(t_splitor *tmp_x)
{
	if (tmp_x != NULL && tmp_x->state == G && tmp_x->type != '\"'
		&& tmp_x->type != '\'' && tmp_x->type != '|')
		return (1);
	else if (tmp_x != NULL && (tmp_x->state == D || tmp_x->state == S)
		&& tmp_x->type != '|')
		return (1);
	else if (tmp_x != NULL && (tmp_x->state == D || tmp_x->state == S))
		return (1);
	return (0);
}

void	ft_neuter_cmd(t_command **new_node, int *i, t_splitor **tmp_x)
{
	if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
		&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
	{
		(*new_node)->arg[*i] = ft_strdup((*tmp_x)->in);
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
		(*tmp_x) = (*tmp_x)->next;
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S)
		&& (*tmp_x)->type != '|')
	{
		(*new_node)->arg[*i] = ft_strdup("");
		while (tmp_x != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		{
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
					(*tmp_x)->in);
			(*tmp_x) = (*tmp_x)->next;
		}
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
	}
	else if ((*tmp_x) != NULL)
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && (*tmp_x)->type != '|')
	{
		if ((*tmp_x) != NULL && (*tmp_x)->type != ' ')
			ft_neuter_cmd(new_node, i, tmp_x);
		ft_skeep_space(tmp_x);
	}
}

t_command	*ft_new_command(int count, t_splitor **tmp_x)
{
	t_command	*new_node;
	int			i;

	i = 0;
	new_node = malloc(sizeof(t_command));
	new_node->arg = malloc(sizeof(char *) * (count + 1));
	if (((*tmp_x) != NULL && (*tmp_x)->type == '|'))
	{
		new_node->arg[i] = ft_strdup((*tmp_x)->in);
		i++;
		new_node->arg[i] = NULL;
		new_node->next = NULL;
		(*tmp_x) = (*tmp_x)->next;
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->type != '|')
		ft_not_pipe(&new_node, &i, tmp_x);
	new_node->doc = NULL;
	ft_check_doc(&new_node);
	return (new_node);
}
