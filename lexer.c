/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/12 11:20:46 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_get_state(t_idx *var, char s)
{
	if (var->in_d == -1 && s == '\"' && var->in_s == -1)
		return (var->in_d = 1, G);
	else if (var->in_d == 1 && s == '\"' && var->in_s == -1)
		return (var->in_d = -1, G);
	else if (var->in_d == 1 && ft_isprint(s) && var->in_s == -1)
		return (D);
	else if (var->in_d == -1 && ft_isprint(s) && var->in_s == -1 && s != '\'')
		return (G);
	else if (var->in_s == -1 && s == '\'' && var->in_d == -1)
		return (var->in_s = 1, G);
	else if (var->in_s == 1 && s == '\'' && var->in_d == -1)
		return (var->in_s = -1, G);
	else if (var->in_s == 1 && ft_isprint(s) && var->in_d == -1)
		return (S);
	else if (var->in_s == -1 && ft_isprint(s) && var->in_d == -1 && s != '\"')
		return (G);
	return (3);
}

int	ft_lexer(char *s, t_splitor **x)
{
	t_idx	var;
	int		str_input_len;

	str_input_len = strlen(s);
	var.i = 0;
	var.in_d = -1;
	var.in_s = -1;
	while (var.i < str_input_len)
	{
		var.start = var.i;
		var.len = 0;
		if (s[var.i] && !ft_check_input(s[var.i]))
			ft_get_word(s, &var, x);
		else if (s[var.i] && ft_check_input(s[var.i]))
			ft_get_char(s, &var, x);
	}
	if (var.in_d == 1 || var.in_s == 1 || ft_handler_syn_error(x))
		return (1);
	// print_t_command(*x);
	return (0);
}
