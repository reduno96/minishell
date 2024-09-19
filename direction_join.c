/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 08:32:43 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/19 14:37:54 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dir_join_word_2(char ***arr_join, t_splitor **tmp_x, t_envarment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	// printf("%s\n", (*tmp_x)->in);
	if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$'
		&& j == 1)
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s, 1);
			// printf("i'm here %s\n", (*arr_join)[0]);
			// while(1)
			// ;
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_join_arr(arr_join, s);
		}
	}
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type == -1))
		ft_join_arr(arr_join, (*tmp_x)->in);
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		ft_join_arr(arr_join, (*tmp_x)->in);
	if ((*tmp_x) != NULL && (*tmp_x)->type != ' ')
		(*tmp_x) = (*tmp_x)->next;
	// printf("%s\n", (*tmp_x)->in);
}

void	ft_dir_join_words(char ***arr_join, t_splitor **tmp_x, t_envarment *my_env,
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
				if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
				{
					s = ft_expand((*tmp_x)->in, &my_env);
					ft_split_expand(arr_join, s, 1);
				}
				else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D
					&& j == 1)
				{
					s = ft_expand((*tmp_x)->in, &my_env);
					ft_join_arr(arr_join, s);
				}
			}
			else if ((*tmp_x) != NULL)
			{
				// printf("%d\n", (*tmp_x)->state);
				// printf("%d\n", (*tmp_x)->type);
				ft_join_arr(arr_join, (*tmp_x)->in);
			}
			(*tmp_x) = (*tmp_x)->next;
		}
		ft_dir_join_word_2(arr_join, tmp_x, my_env, j);
	}
}

char	**ft_split_expand(char ***arr_join, char *s, int bo)
{
	char	**expand_split;
	int		i;

	i = 0;
	// (void)join;
	(void)bo;
	if (s == NULL)
		return (0);
	expand_split = ft_split(s, ' ');
	if (ft_len_arg(expand_split) == 1)
		ft_join_arr(arr_join, expand_split[0]);
	else
		*arr_join = ft_join_arg(*arr_join, expand_split);
	// printf("_______________in split expand\n");
	return (*arr_join);
}
void	ft_join_arr(char ***arr_join, char *in)
{
	int	len_of_arr;

	len_of_arr = ft_len_arg(*arr_join);
	if (len_of_arr == 0)
	{
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(in);
		(*arr_join)[1] = NULL;
	}
	else
	{
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr],
				ft_strdup(in));
	}
}
char	**ft_word(t_splitor **tmp_x, t_envarment *my_env, int j,
		char ***arr_join)
{
	char	*s;
	char	*join;

	join = NULL;
	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type != ' '
			&& ((*tmp_x)->type == '$' || !ft_condition((*tmp_x)))))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			// printf("1\n");
			s = ft_expand((*tmp_x)->in, &my_env);
			// printf("End of 1\n");
			ft_split_expand(arr_join, s, 1);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			// printf("2\n");
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s, 0);
		}
		else
		{
			ft_join_arr(arr_join, (*tmp_x)->in);
		}
		(*tmp_x) = (*tmp_x)->next;
		ft_dir_join_words(arr_join, tmp_x, my_env, j);
	}
	return (*arr_join);
}

void	ft_join_next(char ***arr_join, t_splitor **tmp_x, t_envarment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == -1
			|| (*tmp_x)->type == '$'))
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s, 1);
		}
		else
		{
			ft_join_arr(arr_join, (*tmp_x)->in);
			(*tmp_x) = (*tmp_x)->next;
		}
		(*tmp_x) = (*tmp_x)->next;
	}
}
void	ft_join_double(char ***arr_join, t_splitor **tmp_x, t_envarment *my_env,
		int j)
{
	char	*s;

	s = NULL;
	if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$')
		&& j == 1)
	{
		if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_split_expand(arr_join, s, 1);
		}
		else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
		{
			s = ft_expand((*tmp_x)->in, &my_env);
			ft_join_arr(arr_join, s);
		}
		(*tmp_x) = (*tmp_x)->next;
	}
	ft_dir_join_words(arr_join, tmp_x, my_env, 1);
	ft_join_next(arr_join, tmp_x, my_env, 1);
}

char	**ft_double_and_sigle(t_splitor **tmp_x, t_envarment *my_env, int j,
		char ***arr_join)
{
	char	*s;

	s = NULL;
	while (((*tmp_x) != NULL) && ((*tmp_x)->state == D || (*tmp_x)->state == S
			|| (*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
	{
		if ((*tmp_x) != NULL)
		{
			if ((*tmp_x)->type == '$' && (*tmp_x)->state == G && j == 1)
			{
				s = ft_expand((*tmp_x)->in, &my_env);
				ft_split_expand(arr_join, s, 1);
			}
			else if ((*tmp_x)->type == '$' && (*tmp_x)->state == D && j == 1)
			{
				s = ft_expand((*tmp_x)->in, &my_env);
				ft_split_expand(arr_join, s, 0);
			}
			else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
					|| (*tmp_x)->state == S))
				ft_join_arr(arr_join, (*tmp_x)->in);
			else if ((*tmp_x) != NULL && (((*tmp_x)->type == '$')
					|| (*tmp_x)->type == -1))
				ft_join_arr(arr_join, (*tmp_x)->in);
		}
		(*tmp_x) = (*tmp_x)->next;
		ft_join_double(arr_join, tmp_x, my_env, j);
	}
	return (*arr_join);
}
