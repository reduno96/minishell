/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:34 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/22 12:54:42 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset(t_envarment *var, t_command *list)
{
	t_envarment *env, *env_1;
	env = var;
	env_1 = var;
	int i = 1;

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
	return (1);
}