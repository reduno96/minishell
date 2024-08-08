/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_synx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 07:47:51 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/08 11:15:42 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_env(t_splitor **x, t_envarment *my_env)
{
	t_splitor	*tmp_cmd;
	t_envarment	*tmp_env;

	tmp_cmd = *x;
	tmp_env = my_env;
	while (tmp_cmd != NULL)
	{
		if (tmp_cmd->type == '$' && tmp_cmd->state != S)
		{
			while (tmp_env != NULL)
			{
				if (ft_search(tmp_env->var, tmp_cmd->in + 1))
				{
					free(tmp_cmd->in);
					tmp_cmd->in = ft_strdup(tmp_env->data);
					break ;
				}
				tmp_env = tmp_env->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
}

int	ft_condtion(t_splitor *start)
{
	if ((start->type != ' ' && start->type != -1 && start->type != '$'
			&& start->type != '\'' && start->type != '\"'))
		return (1);
	return (0);
}

int	ft_check_between(t_splitor **start)
{
	while ((*start) != NULL)
	{
		if ((*start)->type == '|' || (ft_condtion(*start)
				&& ((*start)->state == G)))
		{
			if ((*start) != NULL)
				(*start) = (*start)->next;
			ft_skeep_space(&(*start));
			if ((*start) == NULL || (ft_condtion(*start)))
				return (1);
		}
		else if (ft_condtion(*start) && (*start)->state != G)
			while (((*start) != NULL) && (ft_condtion(*start)
					&& (*start)->state != G))
				(*start) = (*start)->next;
		else if (!ft_condtion(*start) && (*start)->state != G)
			while (((*start) != NULL) && !ft_condtion(*start)
				&& (*start)->state != G)
				(*start) = (*start)->next;
		else if (((*start) != NULL) && (*start)->state == G)
			(*start) = (*start)->next;
	}
	return (0);
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
	if (ft_check_between(&start))
		return (1);
	start = *x;
	end = ft_lstlast(start);
	if (end->type == '|')
		return (1);
	return (0);
}

void	check_syn(t_splitor **x)
{
	if (ft_handler_syn_error(x))
	{
		ft_putstr_fd("Syntax Error:\n", 2);
		// exit(1);
	} // if (ft_check_expand(x))
		// 	printf("and I'm here");
}
