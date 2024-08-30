/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:34 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/27 17:34:38 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envarment 	*delet_first_node(t_envarment   *env)
{
	if (env == NULL)
		return (NULL);
	t_envarment *tmp;
	tmp = env;
	env = env->next;
	free(tmp);
	return (env);
}

void	ft_unset(t_envarment *var, t_command *list)
{
	t_envarment *env, *env_1;
	env = var;
	int i = 1;
	
	if(ft_strcmp(var->var, list->arg[1]) == 0)
	{
		env = delet_first_node(env);
	}
	env_1 = env;
// printf("var-> var = %s\n", var->var);
// printf("list->arg[0] = %s\n", list->arg[1]);
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

