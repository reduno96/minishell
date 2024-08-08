/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:47:51 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/08 10:34:06 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_check_env(t_splitor **x, t_envarment *my_env)
{
	t_splitor	*tmp_cmd;
	t_envarment	*tmp_env;

	// int			len;
	tmp_cmd = *x;
	tmp_env = my_env;
	while (tmp_cmd != NULL)
	{
		if (tmp_cmd->type == '$' && tmp_cmd->state != S)
		{
			while (tmp_env != NULL)
			{
				tmp_env = tmp_env->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
}

int	ft_handler_syn_error(t_splitor **x)
{
	t_splitor	*start;
	t_splitor	*end;

	if (!(*x))
		return (0);
	start = *x;
	if (start->type == '|' || ((start->type != ' ' && start->type != -1
				&& start->type != '$') && start->next == NULL)
		|| ((start->type == '\'' || start->type == '\"')
				&& start->next == NULL))
		return (1);
	while (start != NULL)
	{
		if (start->type == '|' || (((start->type != ' ' && start->type != -1
						&& start->type != '$' && start->type != '\''
						&& start->type != '\"')) && (start->state == G)))
		{
			printf("1\n");
			if (start != NULL)
				start = start->next;
			ft_skeep_space(&start);
			if (start == NULL || (start->type != ' ' && start->type != -1
					&& start->type != '$' && start->type != '\''
					&& start->type != '\"'))
			{
				return (1);
			}
		}
		else if (((start->type != ' ' && start->type != -1 && start->type != '$'
					&& start->type != '\'' && start->type != '\"'))
					&& start->state != G)
		{
			printf("2\n");
			while ((start != NULL) && ((start->type != ' ' && start->type != -1
						&& start->type != '$' && start->type != '\''
						&& start->type != '\"')) && start->state != G)
				start = start->next;
		}
		else if (!((start->type != ' ' && start->type != -1
					&& start->type != '$' && start->type != '\''
					&& start->type != '\"')) && start->state != G)
		{
			printf("3\n");
			while ((start != NULL) && !((start->type != ' ' && start->type != -1
						&& start->type != '$' && start->type != '\''
						&& start->type != '\"')) && start->state != G)
				start = start->next;
		}
		else
		{
			printf("4\n");
			if ((start != NULL) && start->state == G)
				start = start->next;
		}
	}
	start = *x;
	end = ft_lstlast(start);
	if (end->type == '|')
		return (1);
	return (0);
}

void	check_syn(t_splitor **x)
{
	// (void)x;
	if (ft_handler_syn_error(x))
	{
		ft_putstr_fd("Syntax Error:\n", 2);
		// exit(1);
	} // if (ft_check_expand(x))
		// 	printf("and I'm here");
}
