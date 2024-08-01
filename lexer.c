/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/31 10:58:34 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_get_state(t_idx *var, char str_input)
{
	if (var->in_d_quote == -1 && str_input == '\"' && var->in_s_quote == -1)
		return (var->in_d_quote = 1, GENERAL);
	else if (var->in_d_quote == 1 && str_input == '\"' && var->in_s_quote == -1)
		return (var->in_d_quote = -1, GENERAL);
	else if (var->in_d_quote == 1 && ft_isprint(str_input) && var->in_s_quote ==
		-1)
		return (IN_DQUOTE);
	else if (var->in_d_quote == -1 && ft_isprint(str_input)
		&& var->in_s_quote == -1 && str_input != '\'')
		return (GENERAL);
	else if (var->in_s_quote == -1 && str_input == '\'' && var->in_d_quote ==
		-1)
		return (var->in_s_quote = 1, GENERAL);
	else if (var->in_s_quote == 1 && str_input == '\'' && var->in_d_quote == -1)
		return (var->in_s_quote = -1, GENERAL);
	else if (var->in_s_quote == 1 && ft_isprint(str_input) && var->in_d_quote ==
		-1)
		return (IN_SQUOTE);
	else if (var->in_s_quote == -1 && ft_isprint(str_input)
		&& var->in_d_quote == -1 && str_input != '\"')
		return (GENERAL);
	return (3);
}

void	ft_get_word(char *str_input, t_idx *var, t_splitor **x)
{
	while (str_input[var->i] && !ft_check_input(str_input[var->i]))
	{
		var->state = ft_get_state(var, str_input[var->i]);
		var->i++;
		var->len++;
	}
	ft_add(x, ft_lstnew(ft_substr(str_input, var->start, var->len), var->len,
			WORD, var->state));
}

void	ft_her_dir(t_splitor **x, t_idx *var, char *str_input)
{
	var->len++;
	var->i++;
	if (var->len >= 1 && str_input[var->i] == '<')
		ft_add(x, ft_lstnew(ft_substr(str_input, var->start, var->len),
				var->len, HERE_DOC, ft_get_state(var, str_input[var->i])));
	else if (var->len >= 1 && str_input[var->i] == '>')
		ft_add(x, ft_lstnew(ft_substr(str_input, var->start, var->len),
				var->len, DREDIR_OUT, ft_get_state(var, str_input[var->i])));
}

void	ft_get_char(char *str_input, t_idx *var, t_splitor **x)
{
	var->len++;
	if (str_input[var->i] == '$' && !ft_check_input(str_input[var->i + 1]))
	{
		while (str_input[var->i] && !ft_check_input(str_input[var->i + 1]))
		{
			var->state = ft_get_state(var, str_input[var->i]);
			var->i++;
			var->len++;
		}
		ft_add(x, ft_lstnew(ft_substr(str_input, var->start, var->len),
				var->len, ENV, var->state));
	}
	else
	{
		if ((str_input[var->i] == '>' && str_input[var->i + 1] == '>')
			|| (str_input[var->i] == '<' && str_input[var->i + 1] == '<'))
			ft_her_dir(x, var, str_input);
		else
			ft_add(x, ft_lstnew(ft_substr(str_input, var->start, var->len),
					var->len, ft_get_token(str_input[var->i]), ft_get_state(var,
						str_input[var->i])));
	}
	var->i++;
}

void	ft_lexer(char *str_input, t_splitor **x)
{
	t_idx	var;

	var.i = 0;
	var.in_d_quote = -1;
	var.in_s_quote = -1;
	while (str_input[var.i])
	{
		var.start = var.i;
		var.len = 0;
		if (str_input[var.i] && !ft_check_input(str_input[var.i]))
			ft_get_word(str_input, &var, x);
		else if (str_input[var.i] && ft_check_input(str_input[var.i]))
			ft_get_char(str_input, &var, x);
	}
	check_syn(x);
	print_t_command(*x);
}
