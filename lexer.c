/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/26 14:58:32 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

void	ft_enter_in_node(t_command *x, int i, int k, char *str_input)
{
	x->str_input = malloc(sizeof(char) * (k + 1));
	ft_strlcpy(x->str_input, str_input, i);
	x->len = i;
	printf("%s\n", x->str_input);
}

void	ft_lexer(char *str_input, t_command **x)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str_input[i])
	{
		if (ft_isspace(str_input[i]) && ft_isascii(str_input[i + 1]))
			k++;
		i++;
	}
	printf("%d\n", k);
	*x = malloc(sizeof(t_command) * (k + 1));
	k = 0;
	i = 0;
	while (str_input[i])
	{
		k = 0;
		while (ft_isspace(str_input[i]))
			i++;
		if (!ft_isspace(str_input[i]))
		{
			while (!ft_isspace(str_input[i]) && str_input[i])
			{
				i++;
				k++;
			}
		}
		else
		{
			ft_enter_in_node(*x, i, k, str_input);
			break ;
		}
	}
}

// redouane el morabet