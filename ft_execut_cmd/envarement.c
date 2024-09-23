/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:55:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/21 12:00:19 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_var(t_envarment *var)
{
	t_envarment	*tmp;
	int			size;

	if (var == NULL)
		return (0);
	tmp = var;
	size = 0;
	while (tmp != NULL)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**array_env(t_envarment **var)
{
	t_envar		arry;
	int			i;
	t_envarment	*tmp_cmd;

	tmp_cmd = *var;
	arry.len = len_var(*var);
	arry.env_v = (char **)malloc(sizeof(char *) * (arry.len + 1));
	if (arry.env_v == NULL)
		return (NULL);
	i = 0;
	while (i < arry.len)
	{
		arry.var_1 = ft_strdup(tmp_cmd->var);
		arry.var_2 = ft_strdup(tmp_cmd->data);
		arry.res = ft_strjoin(arry.var_1, "=");
		arry.env_v[i] = ft_strjoin(arry.res, arry.var_2);
		free(arry.var_2);
		i++;
		tmp_cmd = tmp_cmd->next;
	}
	arry.env_v[i] = NULL;
	return (arry.env_v);
}

char	*ft_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (0);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
	{
		ptr[i] = s2[j];
		j++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_free_leaks(t_command *list)
{
	int	i;

	i = 0;
	while (list->ar_env[i])
	{
		free(list->ar_env[i]);
		i++;
	}
	free(list->ar_env);
}
