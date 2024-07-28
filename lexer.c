/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/28 12:35:21 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

void	print_t_command(t_command *cmd)
{
	if (cmd == NULL)
	{
		printf("Command is NULL\n");
		return ;
	}
	while (cmd != NULL)
	{
		printf("str_input: %s | ", cmd->str_input);
		printf("len: %d			| ", cmd->len);
		printf("token: %d		| ", cmd->type);
		if (cmd->state == 2)
			printf("state: GENERAL 		|\n");
		if (cmd->state == 1)
			printf("state: IN_SINGLE	|\n");
		if (cmd->state == 0)
			printf("state: IN_DOUBLE	|\n");
		cmd = cmd->next;
		printf("--------------------\n");
	}
}

enum e_token	ft_get_token(char str_input)
{
	if (str_input == ' ')
		return (WHITE_SPACE);
	else if (str_input == '\n')
		return (NEW_LINE);
	else if (str_input == '\'')
		return (QOUTE);
	else if (str_input == '\"')
		return (DOUBLE_QUOTE);
	else if (str_input == '$')
		return (ENV);
	else if (str_input == '|')
		return (PIPE_LINE);
	else if (str_input == '<')
		return (REDIR_IN);
	else if (str_input == '>')
		return (REDIR_OUT);
	return (0);
}

int	ft_check_input(char str_input)
{
	if (str_input == '|' || str_input == '<' || str_input == '>'
		|| str_input == '$' || str_input == '\'' || str_input == '\"'
		|| ft_isspace(str_input))
		return (1);
	return (0);
}

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

void	ft_get_word(char *str_input, t_idx *var, t_command **x)
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

void	ft_get_char(char *str_input, t_idx *var, t_command **x)
{
	var->len++;
	if (str_input[var->i] == '$' && !ft_check_input(str_input[var->i + 1]))
	{
		printf("I'm Here\n");
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
		if (str_input[var->i] == '>' && str_input[var->i + 1] == '>')
		{
			var->len++;
			var->i++;
		}
		ft_add(x, ft_lstnew(ft_substr(str_input, var->start, var->len),
				var->len, ft_get_token(str_input[var->i]), ft_get_state(var,
					str_input[var->i])));
	}
	var->i++;
}
void	ft_lexer(char *str_input, t_command **x)
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
	print_t_command(*x);
}
