/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:23:44 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/28 18:28:10 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_search(char *s, char *d)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == d[i])
			i++;
		else if (d[i] == '\0')
			return (1);
		else
			break ;
	}
	return (0);
}

int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n'));
}

t_token	ft_get_token(char str_input)
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
