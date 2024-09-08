/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:55:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/07 15:00:42 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_var(t_envarment *var)
{
	t_envarment	*tmp;
	int			size;

	tmp = var;
	size = 0;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**array_env(t_envarment *var)
{
	char	**env_v;
	int		len;
	int		i;
	char	*tmp;

	len = len_var(var);
	env_v = (char **)malloc(sizeof(char *) * (len + 1));
	if (env_v == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env_v[i] = (char *)malloc(sizeof(char) * (ft_strlen(var->var)
					+ ft_strlen(var->data) + 2));
		tmp = ft_strjoin_1(var->var, "=");
		env_v[i] = ft_strjoin_1(tmp, var->data);
		i++;
		var = var->next;
	}
	env_v[i] = NULL;
	return (env_v);
}
