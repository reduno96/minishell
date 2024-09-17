/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:32:43 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/17 15:35:56 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_join_word_2(char **join, t_splitor **tmp_x, t_envarment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$'
		&& j == 1)
	{
		s = ft_expand((*tmp_x)->in, &my_env);
		*join = ft_strjoin(*join, s);
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type == -1))
		*join = ft_strjoin(*join, (*tmp_x)->in);
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		*join = ft_strjoin(*join, (*tmp_x)->in);
	if ((*tmp_x) != NULL && (*tmp_x)->type != ' ')
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_join_words(char **join, t_splitor **tmp_x, t_envarment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		if (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		while ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
		{
			if ((*tmp_x) != NULL && (*tmp_x)->state != S
				&& (*tmp_x)->type == '$' && j == 1)
			{
				s = ft_expand((*tmp_x)->in, &my_env);
				*join = ft_strjoin(*join, s);
			}
			else if ((*tmp_x) != NULL)
				*join = ft_strjoin(*join, (*tmp_x)->in);
			(*tmp_x) = (*tmp_x)->next;
		}
		ft_join_word_2(join, tmp_x, my_env, j);
	}
}

char	*ft_word(t_splitor **tmp_x, t_envarment *my_env, int j)
{
	char	*s;
	char	*join;

	join = NULL;
	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type != ' '
			&& ((*tmp_x)->type == '$' || !ft_condition((*tmp_x)))))
	{
		if ((*tmp_x)->type == '$' && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);

			if (s == NULL)
			{
				if (join == NULL)
					join = NULL;
				else
					join = ft_strjoin(join, ft_strdup(""));
			}
			else
				join = ft_strjoin(join, s);
		}
		else
			join = ft_strjoin(join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_join_words(&join, tmp_x, my_env, j);
	}
	return (join);
}

void	ft_join_double( char **join, t_splitor **tmp_x,
		t_envarment *my_env, int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$') && j == 1)
	{

		s = ft_expand((*tmp_x)->in, &my_env);
		*join = ft_strjoin(*join, s);
		(*tmp_x) = (*tmp_x)->next;
	}
	ft_join_words(join, tmp_x, my_env, 1);
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == -1
			|| (*tmp_x)->type == '$'))
	{
		if ((*tmp_x)->type == '$' && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			*join = ft_strjoin(*join, s);
			(*tmp_x) = (*tmp_x)->next;
		}
		else
		{
			*join = ft_strjoin_1(*join, (*tmp_x)->in);
			(*tmp_x) = (*tmp_x)->next;
		}
	}
}

char	*ft_double_and_sigle(t_splitor **tmp_x, t_envarment *my_env, int j)
{
	char	*s;
	char	*join;

	join = NULL;
	s = NULL;
	while (((*tmp_x) != NULL) && ((*tmp_x)->state == D || (*tmp_x)->state == S
			|| (*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
	{
		if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$') && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			join = ft_strjoin(join, s);
		}
		else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
			join = ft_strjoin_1(join, (*tmp_x)->in);
		else if ((*tmp_x) != NULL && (((*tmp_x)->type == '$')
				|| (*tmp_x)->type == -1))
			join = ft_strjoin_1(join, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_join_double( &join, tmp_x, my_env, j);
	}
	return (join);
}
