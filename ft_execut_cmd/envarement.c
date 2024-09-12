/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envarement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:55:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/12 07:45:35 by rel-mora         ###   ########.fr       */
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
	char	*tmp;
	t_envarment *tmp_cmd;

	tmp_cmd = *var;

	len = len_var(*var);

	env_v = (char **)malloc(sizeof(char *) * (len + 1));
	if (env_v == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env_v[i] = (char *)malloc(sizeof(char) * (ft_strlen(tmp_cmd->var)
					+ ft_strlen(tmp_cmd->data) + 2));
		tmp = ft_strjoin_1(tmp_cmd->var, "=");
		env_v[i] = ft_strjoin_1(tmp, tmp_cmd->data);
		free(tmp);
		i++;
		tmp_cmd = tmp_cmd->next;
	}
	env_v[i] = NULL;
	return (env_v);
}
