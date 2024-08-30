/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/30 08:10:38 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_spaces(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && (*tmp_x)->type == ' ')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_quote(t_splitor **tmp_x, int *i, t_command **new_node)
{
	(*tmp_x) = (*tmp_x)->next;
	if (((*tmp_x) != NULL && (*tmp_x)->state == G) && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
	}
}

void	ft_skip(t_splitor **tmp_x, int *i, t_command **new_node)
{
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		while (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		if ((*tmp_x) != NULL)
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
					(*tmp_x)->in);
		if ((*tmp_x) != NULL)
			(*tmp_x) = (*tmp_x)->next;
	}
}
void	ft_double_and_sigle(t_splitor **tmp_x, int *i, t_command **new_node)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_skip(tmp_x, i, new_node);
	}
	(*i)++;
	(*new_node)->arg[*i] = NULL;
	(*new_node)->next = NULL;
}

void	ft_general_command(t_command **new_node, int *i, t_splitor **tmp_x)
{
	printf("HI I'M IN ELSE IN GENERAL FUNCTION \n");
	(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], (*tmp_x)->in);
	(*tmp_x) = (*tmp_x)->next;
	ft_skip(tmp_x, i, new_node);
	(*i)++;
	(*new_node)->arg[*i] = NULL;
	(*new_node)->next = NULL;
}
void	ft_neuter_cmd(t_command **new_node, int *i, t_splitor **tmp_x)
{
	if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
		&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
		ft_general_command(new_node, i, tmp_x);
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		ft_double_and_sigle(tmp_x, i, new_node);
	else if (((*tmp_x) != NULL && (*tmp_x)->state == G)
		&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
		ft_skip_quote(tmp_x, i, new_node);
	else if ((*tmp_x) != NULL)
		(*tmp_x) = (*tmp_x)->next;
}
void	ft_skip_not_word(t_splitor **tmp_x, t_envarment *my_env)
{
	(void)my_env;
	if ((*tmp_x)->type == '<' || (*tmp_x)->type == '>'
		|| (*tmp_x)->type == DREDIR_OUT || (*tmp_x)->type == HERE_DOC)
	{
		printf("HI im in ficton skip not word\n\n");
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		if ((*tmp_x) != NULL)
			(*tmp_x) = (*tmp_x)->next;
	}
	printf("HI im in ficton skip not word\n\n");
}
void	ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	while ((*tmp_x) != NULL && !((*tmp_x)->type == '|' && (*tmp_x)->state == G))
	{
		if ((*tmp_x) != NULL && (*tmp_x)->type != -1)
			ft_skip_not_word(tmp_x, my_env);
		if ((*tmp_x) != NULL && !((*tmp_x)->type == ' '
				&& (*tmp_x)->state == G))
			ft_neuter_cmd(new_node, i, tmp_x);
		if ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_skip_spaces(tmp_x);
	}
	printf(" ft_not_pipe\n\n");
}
