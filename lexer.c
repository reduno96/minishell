/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/25 16:42:35 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

void	ft_lexer(char *str_input)
{
    t_command
	int	i;

	i = 0;
	while (str_input[i])
	{
		if (ft_isspace(str_input[i]))
		{

		}
		i++;
	}
}

// redouane el morabet