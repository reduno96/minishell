/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodes_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:13:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/15 10:06:46 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_go_to_env(char **s, char *arg, int *i, t_envarment **my_env)
{
	t_envarment	*tmp_env;

	*s = NULL;

	tmp_env = *my_env;
	while (tmp_env != NULL)
	{
		if (ft_search(tmp_env->var, arg + (*i)))
		{
			*s = ft_strdup(tmp_env->data);
			break ;
		}
		else
			*s = NULL;
		tmp_env = tmp_env->next;
	}
}

char	*ft_expand(char *arg, t_envarment **my_env)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (arg[i])
	{
		if (arg[i + 1] == '?')
		{
			return (s = ft_strdup(ft_itoa(g_exit_status)), s);
		}
		else if (arg[1] == '\0')
			return (s = ft_strdup("$"), s);
		else if (arg[i] == '$')
		{
			i++;
			if (arg[i] == '\0')
				break ;
			if(!ft_isalnum(arg[i]))
				ft_strdup("");
			ft_go_to_env(&s, arg, &i, my_env);
		}
		i++;
	}
	return (s);
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

	if (!lst || !new)
		return ;
	p = *lst;
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
	int			i;
	int			j;

	var = NULL;
	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				add_back_node(&var, new_node(ft_substr(env[i], 0, j),
						ft_substr(env[i], j + 1, ft_strlen(env[i] + j))));
				break ;
			}
			j++;
		}
		i++;
	}
	return (var);
}
