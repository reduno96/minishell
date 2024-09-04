/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:23:44 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/04 12:50:16 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t_command(t_splitor *cmd)
{
	(void)cmd;
	// if (cmd == NULL)
	// {
	// 	printf("Command is NULL\n");
	// 	return ;
	// }
	// while (cmd != NULL)
	// {
	// 	printf("str_input: %s | ", cmd->in);
	// 	printf("len: %d			| ", cmd->len);
	// 	printf("token: %d		| ", cmd->type);
	// 	if (cmd->state == 2)
	// 		printf("state: GENERAL 		|\n");
	// 	if (cmd->state == 1)
	// 		printf("state: IN_SINGLE	|\n");
	// 	if (cmd->state == 0)
	// 		printf("state: IN_DOUBLE	|\n");
	// 	cmd = cmd->next;
	// 	printf("--------------------\n");
	// }
}

int	ft_search(char *s, char *d)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(s);
	while (s[i] && s[i])
	{
		if (s[i] == d[j])
			j++;
		if (len == j && s[i + 1] == d[j])
			return (1);
		i++;
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
