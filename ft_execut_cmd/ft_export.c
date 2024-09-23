/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/22 19:05:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_eqal(char *ptr, char c)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	**split_line(char *ptr)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 3);
	if (ft_str_eqal(ptr, '=') == 1)
	{
		arg[0] = first_word(ptr);
		arg[1] = ft_strdup(ft_strchr(ptr, '=') + 1);
		if (arg[1][0] == '\0')
		{
			free(arg[1]);
			arg[1] = ft_strdup("=");
		}
	}
	else
	{
		arg[0] = ft_strdup(ptr);
		arg[1] = ft_strdup("");
	}
	if (arg[0] == NULL || arg[1] == NULL)
	{
		free_args(arg);
		return (NULL);
	}
	arg[2] = NULL;
	return (arg);
}

int	check_is_valid_1(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=')
	{
		ft_error(str, "export :`");
		return (1);
	}
	if (ft_isdigit(str[0]))
	{
		ft_error(str, "export :`");
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if (str[i] < '0' || (str[i] >= ':' && str[i] <= '@') || (str[i] >= '['
				&& str[i] <= '^') || str[i] >= '{' || str[i] == '`')
		{
			ft_error(str, "export :`");
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_1(t_envarment **var, t_command *str, int *i)
{
	char		*ptr_1;
	char		*ptr_2;
	t_envarment	*elem;
	char		**list;

	list = split_line(str->arg[*i]);
	ptr_1 = ft_strdup(list[0]);
	ptr_2 = ft_strdup(list[1]);
	if (test_exist(var, list) == 0)
	{
		(*i)++;
	}
	else if (test_exist(var, list) == 1)
	{
		elem = new_node(ptr_1, ptr_2);
		add_back_node(var, elem);
		(*i)++;
	}
	free_args(list);
	return ;
}

void	ft_export(t_envarment **var, t_command *str)
{
	int	i;

	i = 1;
	while (str->arg[i] != NULL)
	{
		if (str->arg[i][0] == '\0')
			i++;
		else
		{
			if (check_is_valid_1(str->arg[i]) == 1)
				return ;
			export_1(var, str, &i);
		}
	}
	affiche_export(str->arg, var);
}
