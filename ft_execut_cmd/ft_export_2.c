/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:02:41 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/26 12:21:53 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	affiche_export(char **str, t_environment **var)
{
	int		i;
	int		count;
	char	*ptr;

	count = 0;
	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '\0')
		{
			ptr = str[i];
			count++;
		}
		i++;
	}
	if (count == 1)
	{
		if (ft_strcmp(ptr, "export") == 0)
			print_export(var);
	}
}

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	test_exist(t_environment **var, char **list)
{
	t_environment	*ptr;

	if (var == NULL || *var == NULL)
		return (-1);
	ptr = *var;
	while (ptr)
	{
		if ( list[0] != NULL && ft_strcmp(ptr->var, list[0]) == 0)
		{
			if (list[1] != NULL && ft_strcmp(ptr->data, list[1]) == 0)
				return (0);
			else
			{
				if (list[1] == NULL)
					return (0);
				free(ptr->data);
				ptr->data = ft_strdup(list[1]);
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}

void	free_args(char **args)
{
	int	i;

	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		if (args[i] != NULL)
		{
			free(args[i]);
			args[i] = NULL;
		}
		i++;
	}
	free(args);
	args = NULL;
}

char	*first_word(char *ptr)
{
	int		i;
	char	*str;

	i = 0;
	while (ptr[i] && ptr[i] != '=')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (ptr[i] && ptr[i] != '=')
	{
		str[i] = ptr[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
