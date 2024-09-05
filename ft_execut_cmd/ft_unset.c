/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:34 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/01 23:42:20 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envarment	*delet_first_node(t_envarment *env)
{
	t_envarment	*tmp;

	if (env == NULL)
		return (NULL);
	tmp = env;
	env = env->next;
	free(tmp);
	return (env);
}

void	ft_unset(t_envarment *var, t_command *list)
{
	int			i;
	t_envarment	*env;
	t_envarment	*env_1;

	env = var;
	i = 1;
	if (ft_strcmp(var->var, list->arg[1]) == 0)
		env = delet_first_node(env);
	env_1 = env;
	while (list->arg[i])
	{
		while (env_1)
		{
			if (ft_strcmp(env_1->var, list->arg[i]) == 0)
			{
				env->next = env_1->next;
				free(env_1);
			}
			env = env_1;
			env_1 = env_1->next;
		}
		env = var;
		env_1 = var;
		i++;
	}
}
