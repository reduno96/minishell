/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/07 07:34:15 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_command(t_command **lst, t_command *new)
{
	t_command	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_last_command(*lst);
		last->next = new;
	}
}

t_command	*ft_last_command(t_command *lst)
{
	t_command	*last;

	last = lst;
	if (!lst)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_count_d_s(t_splitor **tmp, int *count)
{
	while ((*tmp) != NULL && ((*tmp)->state == D || (*tmp)->state == S))
		(*tmp) = (*tmp)->next;
	(*count)++;
}

void	ft_count_parameters(t_splitor *tmp_x, int *count)
{
	t_splitor	*tmp;

	tmp = tmp_x;
	if (tmp != NULL && tmp->type == '|')
		(*count)++;
	else if (tmp != NULL && tmp->type != '|')
	{
		while (tmp != NULL && tmp->type != '|')
		{
			ft_skeep_space(&tmp);
			if (tmp != NULL && tmp->state == G && tmp->type != '\"'
				&& tmp->type != '\'' && tmp->type != '|')
			{
				(*count)++;
				tmp = tmp->next;
			}
			else if (tmp != NULL && (tmp->state == D || tmp->state == S)
				&& tmp->type != '|')
				ft_count_d_s(&tmp, count);
			else if (tmp != NULL && tmp->type != '|')
				tmp = tmp->next;
		}
	}
}

void	ft_command(t_splitor **x, t_environment **my_env, t_command **cmd)
{
	int			count;
	t_splitor	*tmp_x;
	t_command	*tmp_cmd;
	int			i;

	(void)my_env;
	tmp_x = *x;
	while (tmp_x != NULL)
	{
		count = 0;
		ft_count_parameters(tmp_x, &count);
		printf("Count: %d\n", count);
		ft_add_command(cmd, ft_new_command(count, &tmp_x));
	}
	tmp_cmd = *cmd;
	while (tmp_cmd != NULL)
	{
		i = 0;
		while (tmp_cmd->arg[i] != NULL)
		{
			printf("Argument: %s\n", tmp_cmd->arg[i]);
			i++;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
