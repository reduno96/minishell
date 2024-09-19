/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/19 12:31:57 by rel-mora         ###   ########.fr       */
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

int	ft_ckeck_repeate_quote(char ***arr_join, t_command **new_node, int *i,
		t_splitor **tmp_x)
{
	(void) (i);
	while (((*tmp_x) != NULL && (*tmp_x)->next != NULL && ((*tmp_x)->state == G
				&& (*tmp_x)->next->state == G)) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\''))
		&& ((*tmp_x)->next->next != NULL && ((*tmp_x)->next->next->type != 32 /*
				|| (*tmp_x)->next->next->type == '$' */)))
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
		ft_join_arr(arr_join, ft_strdup(""));
		if ((*arr_join)[0] != NULL)
			(*new_node)->arg = ft_join_arg((*new_node)->arg,  (*arr_join));
		(*new_node)->next = NULL;
		return (1);
	}
	return (0);
}

// int	ft_len_arg(char **arg)
// {
// 	int	i;
// 	i = 0;
// 	while (arg[i] != NULL)
// 		i++;
// 	return (i);
// }

void	ft_free_argment(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
}
char **	ft_join_arg(char **arg, char **join)
{
	int		len_of_arg;
	int		len_of_join;
	char	**new_arg;
	int		idx;
	int		j;

	idx = 0;
	j = 0;
	len_of_arg = ft_len_arg(arg);
	// printf("%d\n", len_of_arg);
	len_of_join = ft_len_arg(join);
	// printf("%d\n", len_of_join);
	new_arg = malloc(((len_of_arg + len_of_join) + 1) * sizeof(char *));
	while (arg[idx] != NULL)
	{
	// printf("begin function ft_join_arg\n");
		new_arg[j] = ft_strdup(arg[idx]);
		j++;
		idx++;
	}
	idx = 0;
	while (join[idx])
	{
		new_arg[j] =ft_strdup(join[idx]) ;
		idx++;
		j++;
	}
	new_arg[j] = NULL;
	ft_free_argment(arg);
	ft_free_argment(join);
	return new_arg;

}
int	ft_check_gene_quote(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env, char ***arr_join)
{
	(void)i;
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
			(*new_node)->arg = ft_join_arg((*new_node)->arg,  (*arr_join));
		return (1);
	}
	return (0);
}

void	ft_neuter_cmd(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env, char ***arr_join)
{
	char	*join;

	join = NULL;
	// printf("in neuter|%s|\n", (*tmp_x)->in);
	if (ft_ckeck_repeate_quote(arr_join, new_node, i, tmp_x))
		return ;
	if (ft_check_gene_quote(new_node, i, tmp_x, my_env, arr_join))
		return ;
	if (((*tmp_x) != NULL && (*tmp_x)->state == G) && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		ft_skip_quote(tmp_x, i, new_node);
	else if ((*tmp_x) != NULL && (*tmp_x)->type != '|')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	char	*s;
	char	**join;

	join = malloc(1 * sizeof(char *));
	join[0] = NULL;
	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type != -1
				&& (*tmp_x)->type != '$'))
			ft_skip_not_word(tmp_x, my_env);
	while ((*tmp_x) != NULL && !((*tmp_x)->type == '|' && (*tmp_x)->state == G))
	{
		/* if ((*tmp_x) != NULL && (*tmp_x)->type == '$'
	&& (*tmp_x)->state != S)
	{
		// while ((*tmp_x) != NULL && (*tmp_x)->type == '$')
		// {
			s = ft_expand((*tmp_x)->in, &my_env);
			if (s == NULL)
				(*tmp_x) = (*tmp_x)->next;
			else
			{
				(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
				(*tmp_x) = (*tmp_x)->next;
			}
	(*i)++;
	(*new_node)->arg[*i] = NULL;
	(*new_node)->next = NULL;
	} */
		// printf("in not pipe %s\n", (*tmp_x)->in);
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type != -1
				&& (*tmp_x)->type != '$'))
			ft_skip_not_word(tmp_x, my_env);
		if ((*tmp_x) != NULL && !((*tmp_x)->type == 32 && (*tmp_x)->state == G))
			ft_neuter_cmd(new_node, i, tmp_x, my_env, &join);
		if ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_skip_spaces(tmp_x);
		// printf("====>%s\n", *join);
		// if ((*tmp_x) != NULL)
		// printf("fianl tmp |%s|\n", (*tmp_x)->in);
		// printf("fianl|%s|\n", (*new_node)->arg[0]);
	}
}
