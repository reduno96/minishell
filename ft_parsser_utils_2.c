/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/11 13:25:04 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_condition_2(t_splitor *tmp_x)
{
	if ((tmp_x->type == ' ' || tmp_x->type == HERE_DOC || tmp_x->type == '<'
			|| tmp_x->type == '>' || tmp_x->type == DREDIR_OUT
			|| tmp_x->type == '\'' || tmp_x->type == '\"'))
		return (1);
	return (0);
}

int	ft_ckeck_repeate_quote(char *join, t_command **new_node, int *i,
		t_splitor **tmp_x)
{
	if (((*tmp_x) != NULL && (*tmp_x)->next != NULL) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\''))
		&& ((*tmp_x)->next->next != NULL && (*tmp_x)->next->next->type == -1))
	{
		(*tmp_x) = (*tmp_x)->next;
		return 1;
	}
	else if (((*tmp_x) != NULL && (*tmp_x)->next != NULL)
		&& (((*tmp_x)->type == '\"' && (*tmp_x)->next->type == '\"')
			|| ((*tmp_x)->type == '\'' && (*tmp_x)->next->type == '\'')))
	{
		join = ft_strdup("");
		(*tmp_x) = (*tmp_x)->next;
		(*new_node)->arg[*i] = join;
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
		return (1);
	}
	return 0;
}

int 	ft_check_gene_quote(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	char	*join;

	join = NULL;
	if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
		&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
	{

		join = ft_word(tmp_x, my_env);
		(*new_node)->arg[*i] = join;
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
		return 1;
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		join = ft_double_and_sigle(tmp_x, my_env);
		(*new_node)->arg[*i] = join;
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
		return 1;
	}
	return 0;
}


void	ft_neuter_cmd(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	char	*join;

	join = NULL;
	if (ft_ckeck_repeate_quote(join, new_node, i, tmp_x))
		return ;
	if (ft_check_gene_quote(new_node, i, tmp_x, my_env))
		return ;
	if (((*tmp_x) != NULL && (*tmp_x)->state == G) && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		ft_skip_quote(tmp_x, i, new_node);
	else if ((*tmp_x) != NULL)
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && (*tmp_x)->type == '$' && (*tmp_x)->state != S)
	{
		while ((*tmp_x) != NULL && (*tmp_x)->type == '$')
		{
			s = ft_expand((*tmp_x)->in, my_env);
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
			(*tmp_x) = (*tmp_x)->next;
		}
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
	}
	while ((*tmp_x) != NULL && !((*tmp_x)->type == '|' && (*tmp_x)->state == G))
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type != -1
				&& (*tmp_x)->type != '$'))
			ft_skip_not_word(tmp_x);
		if ((*tmp_x) != NULL && !((*tmp_x)->type == 32 && (*tmp_x)->state == G))
			ft_neuter_cmd(new_node, i, tmp_x, my_env);
		if ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_skip_spaces(tmp_x);
	}
}
