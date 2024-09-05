/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/05 10:20:11 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum_exp(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || (c == '_') || c == '<' || c == '>');
}

int	test_exist(t_envarment *var, char **list)
{
	t_envarment	*ptr;

	ptr = var;
	while (ptr)
	{
		if (ft_strcmp(ptr->var, list[0]) == 0)
		{
			if (ft_strcmp(ptr->data, list[1]) == 0)
				return (0);
			else
			{
				if (list[1][0] == '\0')
					return (0);
				ptr->data = list[1];
				return (0);
			}
		}
		ptr = ptr->next;
	}
	return (1);
}
void	free_args(char **args)
{
	if (args)
	{
		free(args[0]);
		free(args[1]);
		free(args);
	}
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
	if (arg == NULL)
		return (NULL);
	if (ft_str_eqal(ptr, '=') == 1)
	{
		arg[0] = first_word(ptr);
		arg[1] = ft_strdup(ft_strchr(ptr, '=') + 1);
		if (arg[1][0] == '\0')
		{
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

void	print_export(t_envarment **var)
{
	t_envarment	*ptr;

	ptr = *var;
	while (ptr != NULL)
	{
		if (ptr->data[0] == '\0')
			printf("[Declare -x]  %s\n", (char *)ptr->var);
		else if (ptr->data[0] == '=' && ptr->data[1] == '\0')
			printf("[Declare -x]  %s=\"\"\n", (char *)ptr->var);
		else
			printf("[Declare -x]  %s=\"%s\"\n", (char *)ptr->var,
				(char *)ptr->data);
		ptr = ptr->next;
	}
	return ;
}

void	check_dolar_is(char *str, t_envarment *var, t_command *s)
{
	char	*ptr;
	int		i;

	i = 1;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (ptr == NULL)
		return ;
	if (str[0] == '$')
	{
		while (str[i])
		{
			if (!ft_isalnum_exp(str[i]))
			{
				printf("export: `%s': not a valid identifier\n", str);
				return ;
			}
			i++;
		}
	}
	if (s->arg[2] == NULL || s->arg[2][0] == '\0')
		print_export(&var);
	free(ptr);
}

int	exist_redir(char *ptr)
{
	if (ft_strcmp(ptr, ">") == 0)
		return (1);
	if (ft_strcmp(ptr, ">>") == 0)
		return (1);
	if (ft_strcmp(ptr, "<") == 0)
		return (1);
	return (0);
}

int	var_is_valid(char *ptr)
{
	int		j;
	char	**list;

	if (ptr[0] == '=')
	{
		printf("export: `%s': not a valid identifier\n", ptr);
		return (0);
	}
	if (ft_isdigit(ptr[0]))
	{
		printf("export: `%s': not a valid identifier\n", ptr);
		return (0);
	}
	list = ft_split(ptr, '=');
	if (list[0][0] == '\0' && list[1][0] != '\0')
	{
		printf("export: `%s': not a valid identifier\n", ptr);
		return (0);
	}
	j = 0;
	while (list[0][j])
	{
		if (!ft_isalnum_exp(list[0][j]))
		{
			printf("export: `%s': not a valid identifier\n", ptr);
			return (0);
		}
		j++;
	}
	j = 0;
	while (list[j])
	{
		free(list[j]);
		j++;
	}
	free(list);
	return (1);
}

void	ft_export(t_envarment *var, t_command *str)
{
	char		**list;
	int			i;
	t_envarment	*elem;

	i = 1;
	while (str->arg[i] != NULL)
	{
		if (str->arg[i][0] == '$' && str->arg[i + 1] == NULL)
		{
			check_dolar_is(str->arg[i], var, str);
			return ;
		}
		if (exist_redir(str->arg[i]) == 1)
		{
			if (str->arg[i + 2] == NULL)
				break ;
			i = i + 2;
		}
		else
		{
			if (var_is_valid(str->arg[i]) == 0)
			{
				if (str->arg[i + 1] == NULL)
					return ;
			}
			list = split_line(str->arg[i]);
			if (test_exist(var, list) == 0)
				i++;
			else if (test_exist(var, list) == 1)
			{
				elem = new_node(list[0], list[1]);
				add_back_node(&var, elem);
				i++;
			}
		}
	}
	if (str->arg[1] == NULL || str->arg[1][0] == '\0'
		|| (exist_redir(str->arg[1]) == 1))
		print_export(&var);
}
