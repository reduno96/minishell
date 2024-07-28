/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:25:28 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/28 09:10:21 by rel-mora         ###   ########.fr       */
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
void	print_str_input(void *str_input)
{
	// printf("%s__", (char *)str_input);
}
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
			printf("\033[1;31m state: IN_DOUBLE	|\n\033[0m");
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

void ft_change_state(char str_input, t_idx *var)
{
	if (str_input == '\'')
		var->in_s_quote *= -1;
	else if (str_input == '\"')
		var->in_d_quote *= -1;
}

t_state ft_get_state(t_idx *var, char str_input)
{
	int state = 0;



	if (var->in_d_quote == -1 && str_input == '\"')
		return (GENERAL);
	if (var->in_d_quote == 1 && str_input == '\"')
		return (GENERAL);
	if (var->in_d_quote == 1 && str_input == '\'')
		return (IN_DQUOTE);
	if (var->in_d_quote == 1 && ft_isprint(str_input))
		return (IN_DQUOTE);
	if (var->in_d_quote == -1)
		return (GENERAL);
	if (var->in_s_quote == -1 && str_input == '\'')
		return (GENERAL);
	if (var->in_s_quote == 1 && str_input == '\'')
		return (GENERAL);
	if (var->in_s_quote == 1 && str_input == '\"')
		return (IN_SQUOTE);
	if (var->in_s_quote == 1 && ft_isprint(str_input))
		return (IN_SQUOTE);
	// if (var->in_s_quote == -1 && str_input == '\'')
	// 	return (GENERAL);
	// if (var->in_s_quote == 1 && str_input == '\'')
	// 	return (GENERAL);
	// if (var->in_s_quote == 1 && str_input == '\"')
	// 	return (IN_QUOTE);
	// if (var->in_s_quote == 1 && ft_isprint(str_input))
	// 	return (IN_QUOTE);
	return 2;
}

void	ft_lexer(char *str_input, t_command **x)
{
	t_idx	var;

	var.i = 0;
	var.in_d_quote = -1;
	var.in_s_quote = -1;
	while (str_input[var.i])
	{
		ft_change_state(str_input[var.i], &var);
		var.start = var.i;
		var.len = 0;
		if (str_input[var.i] && !ft_check_input(str_input[var.i]))
		{
			while (str_input[var.i] && !ft_check_input(str_input[var.i]))
			{
				var.i++;
				var.len++;
			}
			ft_add(x, ft_lstnew(ft_substr(str_input, var.start, var.len),
					var.len, WORD, ft_get_state(&var, str_input[var.i])));
		}
		else if (str_input[var.i] && ft_check_input(str_input[var.i]))
		{
			var.len++;
			ft_add(x, ft_lstnew(ft_substr(str_input, var.start, var.len),
					var.len, ft_get_token(str_input[var.i]), ft_get_state(&var, str_input[var.i])));
			var.i++;
		}

	}
	print_t_command(*x);
	free(*x);
	*x = NULL;
	// ft_lstiter(x, print_str_input);
}
