/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/26 19:56:35 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

void	ft_enter_in_node(t_command *x)
{
	int	i;

	i = 0;
	// x[i].str_input = malloc(sizeof(char) * (k + 1));
	// ft_strlcpy(x[i].str_input, str_input, k);
	// x[i].len = k;
}

void	ft_lexer(char *str_input, t_command *x)
{
	int	i;
	int	k;
	int	y;
	int	j;

	i = 0;
	k = 0;
	y = 0;
	while (str_input[i])
	{
		if (str_input[i] && str_input[i] != '|' && str_input[i] != '<'
			&& str_input[i] != '>' && !ft_isspace(str_input[i]))
		{
			while (str_input[i] && str_input[i] != '|' && str_input[i] != '<'
				&& str_input[i] != '>' && !ft_isspace(str_input[i]))
				i++;
		}
		else if (str_input[i] == '|' || str_input[i] == '<'
			|| str_input[i] == '>' || ft_isspace(str_input[i]))
			i++;
		x = malloc(sizeof(t_command) * k);
		k++;
	}
	i = 0;
	j = 0;
	while (i <= k)
	{

	}
}
