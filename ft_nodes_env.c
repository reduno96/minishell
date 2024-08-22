/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodes_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:13:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/22 15:49:24 by rel-mora         ###   ########.fr       */
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
		tmp_env = my_env;
		if (tmp_cmd->type == '$' && tmp_cmd->state != S)
		{
			while (tmp_env != NULL)
			{
				if (ft_strcmp(tmp_env->var, tmp_cmd->in + 1) == 0)
				{
					free(tmp_cmd->in);
					tmp_cmd->in = ft_strdup(tmp_env->data);
					if (ft_search(tmp_cmd->in, " "))
						tmp_cmd->is_amb = 1;
					break ;
				}
				tmp_env = tmp_env->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
}

t_envarment	*new_node(void *var, void *data)
{
	t_envarment	*elem;

	elem = (t_envarment *)malloc(sizeof(t_envarment));
	if (!elem)
		return (NULL);
	elem->var = var;
	elem->data = data;
	elem->next = NULL;
	return (elem);
}

void	add_back_node(t_envarment **lst, t_envarment *new)
{
	t_envarment	*p;

	p = *lst;
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new;
}

t_envarment	*ft_stock_envarment(char **env)
{
	t_envarment	*var;
	char		**list;
	int			i;
	t_envarment	*elem;

	var = NULL;
	i = 0;
	while (env[i])
	{
		list = ft_split(env[i], '=');
		elem = new_node(list[0], list[1]);
		add_back_node(&var, elem);
		i++;
	}
	free(list);
	return (var);
}
