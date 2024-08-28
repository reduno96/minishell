/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 09:08:22 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/27 09:20:24 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *arg, t_envarment *my_env)
{
	t_envarment *tmp_env;
	int i = 0;
	int j = 0;
	char *s;

	s = NULL;

	while (arg[i])
	{
		if (arg[i] == '$')
		{
			j++;
			printf("_____1________\n");
			tmp_env = my_env;
			while (tmp_env != NULL)
			{
				printf("_____2________\n");
				if (ft_search(tmp_env->var, arg + i))
				{
					printf("_____3________\n");
					s = ft_strdup(tmp_env->data);
					break ;
				}
				else
					s = NULL;
				tmp_env = tmp_env->next;
			}
		}
	}