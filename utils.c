/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:47:08 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/25 15:00:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len_arg(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] == NULL)
		return (0);
	while (arg[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	**ft_split_expand(char ***arr_join, char *s, int bo)
{
	char	**expand_split;

	(void)bo;
	if (s != NULL)
	{
		expand_split = ft_split(s, ' ');
		free(s);
	}
	else
		return (NULL);
	if (ft_len_arg(expand_split) == 1)
		ft_join_arr(arr_join, expand_split[0]);
	else
		*arr_join = ft_join_arg(*arr_join, expand_split);
	ft_free_argment(expand_split);
	return (*arr_join);
}

void	ft_join_arr(char ***arr_join, char *in)
{
	int		len_of_arr;
	char	*str;

	len_of_arr = ft_len_arg(*arr_join);
	if (in == NULL)
		return ;
	if (len_of_arr == 0)
	{
		*arr_join = NULL;
		*arr_join = malloc((1 + 1) * sizeof(char *));
		(*arr_join)[0] = ft_strdup(in);
		(*arr_join)[1] = NULL;
	}
	else
	{
		str = ft_strdup(in);
		len_of_arr--;
		(*arr_join)[len_of_arr] = ft_strjoin((*arr_join)[len_of_arr], str);
		free(str);
	}
}

void	ft_free_argment(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return ;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
	free(arg);
	arg = NULL;
}
