/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/22 12:09:23 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ckeck_repeate_quote(char ***arr_join, t_command **new_node,
		t_splitor **tmp_x)
{
	while (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\''))
		&& ((*tmp_x)->next->next != NULL && ((*tmp_x)->next->next->type != 32
				|| (*tmp_x)->next->next->type == '$')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
	}
	if (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\'')))
	{
		(*tmp_x) = (*tmp_x)->next;
		(*tmp_x) = (*tmp_x)->next;
		ft_join_arr(arr_join, "");
		if ((*arr_join)[0] != NULL)
			(*new_node)->arg = ft_join_arg((*new_node)->arg, (*arr_join));
		(*new_node)->next = NULL;
		return (1);
	}
	return (0);
}

char	**ft_join_arg(char **arg, char **join)
{
	t_ps	ps;


	ps.idx = 0;
	ps.j = 0;
	ps.len_of_arg = ft_len_arg(arg);
	ps.len_of_join = ft_len_arg(join);
	ps.new_arg = malloc(((ps.len_of_arg + ps.len_of_join) + 1)
			* sizeof(char *));
	printf("%d\n",(ps.len_of_arg + ps.len_of_join) + 1 );
	ps.new_arg[0] = NULL;
	while (arg[ps.idx] != NULL)
	{
		ps.new_arg[ps.j] =  ft_strdup(arg[ps.idx]);
		ps.j++;
		ps.idx++;
	}
	ps.idx = 0;
	while (join[ps.idx])
	{

		ps.new_arg[ps.j] = ft_strdup(join[ps.idx]);

		ps.idx++;
		ps.j++;
	}
	ps.new_arg[ps.j] = NULL;
	ft_free_argment(arg);
	ft_free_argment(join);
	int i = 0;
	while(ps.new_arg[i] != NULL)
		printf("_____%s\n", ps.new_arg[i++]);
	return (ps.new_arg);
}

int	ft_check_gene_quote(t_command **new_node, t_splitor **tmp_x,
		t_envarment *my_env, char ***arr_join)
{
	if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
		&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
	{
		ft_word(tmp_x, my_env, 1, arr_join);
		if ((*arr_join)[0] != NULL)
			(*new_node)->arg = ft_join_arg((*new_node)->arg, (*arr_join));
		return (1);
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		ft_double_and_sigle(tmp_x, my_env, 1, arr_join);
		if ((*arr_join)[0] != NULL)
			(*new_node)->arg = ft_join_arg((*new_node)->arg, (*arr_join));
		return (1);
	}
	return (0);
}

void	ft_neuter_cmd(t_command **new_node, t_splitor **tmp_x,
		t_envarment *my_env, char ***arr_join)
{
	if (ft_ckeck_repeate_quote(arr_join, new_node, tmp_x))
		return ;
	if (ft_check_gene_quote(new_node, tmp_x, my_env, arr_join))
		return ;
	else if ((*tmp_x) != NULL && (*tmp_x)->type != '|')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_not_pipe(t_command **new_node, t_splitor **tmp_x,
		t_envarment *my_env)
{
	char	**join;

	join = malloc(1 * sizeof(char *));
	join[0] = NULL;
	while ((*tmp_x) != NULL && !((*tmp_x)->type == '|' && (*tmp_x)->state == G))
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type != -1
				&& (*tmp_x)->type != '$'))
			ft_skip_not_word(tmp_x, my_env);
		if ((*tmp_x) != NULL && !((*tmp_x)->type == 32 && (*tmp_x)->state == G))
			ft_neuter_cmd(new_node, tmp_x, my_env, &join);
		if ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_skip_spaces(tmp_x);
	}
}
