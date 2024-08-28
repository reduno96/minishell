/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/28 14:48:27 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_envarment 		*ft_stock_envarment(char **env)
// {
// 	t_envarment *var=NULL;
// 	char **list;
// 	int i =0;
// 	while (env[i])
// 	{
// 		list = ft_split(env[i], '=');
// 		t_envarment *elem = new_node(list[0],list[1]);
// 		add_back_node(&var , elem);
// 		free(list);
// 		i++;
// 	}
// 	return (var);
// }

int	test_exist(t_envarment *var, char **list)
{
	t_envarment	*ptr;

	ptr = var;
	while (ptr)
	{
		if (ft_strcmp(ptr->var, list[0]) == 0 && ft_strcmp(ptr->data,
				list[1]) == 0)
			return (0);
		else if (ft_strcmp(ptr->var, list[0]) == 0 && ft_strcmp(ptr->data,
				list[1]) != 0)
		{
			ptr->data = list[1];
			return (0);
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
char	**split_line(char *ptr)
{
	int		i;
	int		count;
	char	**arg;

	count = 0;
	;
	arg = (char **)malloc(sizeof(char *) * 2);
	if (arg == NULL)
		return (NULL);
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == '=')
			count++;
		i++;
	}
	if (count == 0)
	{
		arg[0] = ft_strdup(ptr);
		arg[1] = ft_strdup("");
	}
	else
	{
		arg[0] = ft_substr(ptr, 0, ft_strchr(ptr, '=') - ptr);
		arg[1] = ft_strdup(ft_strchr(ptr, '=') + 1);
		if (arg[1][0] == '\0')
			arg[1] = ft_strdup("\"\"");
	}
	if (arg[0] == NULL || arg[1] == NULL)
		return (free_args(arg), NULL);
	return (arg);
}
void	print_export(t_envarment *var, t_command *str)
{
	if (str->arg[1] == NULL)
	{
		while (var)
		{
			printf("declare -x %s=\"%s\"\n", (char *)var->var,
				(char *)var->data);
			var = var->next;
		}
	}
}

int	ft_export(t_envarment *var, t_command *str)
{
	char		**list;
	int			i;
	t_envarment	*elem;

	i = 1;
	while (str->arg[i] != NULL)
	{
		list = split_line(str->arg[i]);
		if (test_exist(var, list) == 0)
		{
			i++;
			break ;
		}
		else
		{
			elem = new_node(list[0], list[1]);
			add_back_node(&var, elem);
		}
		free(list);
		i++;
	}
	print_export(var, str);
	return (1);
}
