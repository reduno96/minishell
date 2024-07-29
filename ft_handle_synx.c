/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_synx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:47:51 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/29 16:50:19 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_env(t_environment **my_env, char **env)
{
	t_idx	var;

	var.i = 0;
	if (!env || !(*env))
		return ;
	while (env[var.i])
		ft_add_node(my_env, ft_new_node(ft_strdup(env[var.i++])));
	//  print_env(my_env);
}

int	ft_search_env(char *s, char *d)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(d);
	while (s[i] && s[i])
	{
		if (s[i] == d[j])
			j++;
		if (len == j && s[i + 1] == '=')
			return (i);
		i++;
	}
	return (0);
}

void	ft_check_env(t_splitor **x, t_environment *my_env)
{
	t_splitor		*tmp_cmd;
	t_environment	*tmp_env;
	int				len;

	len = 0;
	tmp_cmd = *x;
	tmp_env = my_env;
	while (tmp_cmd != NULL)
	{
		if (tmp_cmd->type == '$')
		{
			while (tmp_env != NULL)
			{
				len = ft_search_env(tmp_env->line, tmp_cmd->str_input + 1);
				if (len)
				{
					free(tmp_cmd->str_input);
					tmp_cmd->str_input = ft_substr(tmp_env->line, len + 2,
							ft_strlen(tmp_env->line + len + 1));
				}
				tmp_env = tmp_env->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
}

int	ft_handler_syn_error(t_splitor **x)
{
	t_splitor	*end;
	t_splitor	*start;

	if (!(*x))
		return (0);
	start = *x;
	if (start->type == '|' || ((start->type == '<' || start->type == '>')
			&& start->next == NULL) || ((start->str_input[0] == '\''
				|| start->str_input[0] == '\"') && start->next == NULL))
		return (1);
	end = ft_lstlast(start);
	if (end->state == IN_DQUOTE || end->state == IN_SQUOTE || end->type == '|')
		return (1);
	return (0);
}

void	check_syn(t_splitor **x)
{
	if (ft_handler_syn_error(x))
		ft_putstr_fd("Syntax Error:\n", 2);
	// if (ft_check_expand(x))
	// 	printf("and I'm here");
}
