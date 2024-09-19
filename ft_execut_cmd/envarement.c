/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:55:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/17 11:09:21 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_var(t_envarment *var)
{
	t_envarment	*tmp;
	int			size;

	if(var == NULL)
		return 0;

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
	char	**env_v;
	int		len;
	int		i;
	char *var_1;
	char *var_2;
	char *res;
	t_envarment *tmp_cmd;

	tmp_cmd = *var;
	len = len_var(*var);
	env_v = (char **)malloc(sizeof(char *) * (len + 1));
	if (env_v == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		var_1 = ft_strdup(tmp_cmd->var);
		var_2 = ft_strdup(tmp_cmd->data);
		res = ft_strjoin(var_1, "=");
		env_v[i] = ft_strjoin(res, var_2);
		free(var_2);
		i++;
		tmp_cmd = tmp_cmd->next;
	}
	env_v[i] = NULL;
	return (env_v);
}

char	*ft_join(char  *s1, char  *s2)

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
