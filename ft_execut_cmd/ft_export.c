/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:52 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/25 20:45:43 by bouhammo         ###   ########.fr       */
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
char 	*ft_data(char *ptr)
{
	int 	i;
	char 	*s;

	// if(ptr == NULL)
	// 	return NULL;
	i = 0;
	while (ptr[i + 1] != '\0')
	{
		if(ptr[i] == '=' && ptr[i + 1] ==  '=' )
		{
			s = ft_strdup(ptr + i + 1 );
			// printf("ptr ++++++++++  [%s]  \n", s);
			return s;
		}
		i++;
	}
	s =  ft_strdup(ft_strchr(ptr, '='));
	if(s[0] == '=' && s[1] == '\0')
		s = ft_strdup("");
	return s;
}

char	**split_line(char *ptr)
{
	char	**arg;

	arg = (char **)malloc(sizeof(char *) * 3);
	if (ft_str_eqal(ptr, '=') == 1)
	{
		arg[0] = first_word(ptr);
		arg[1]  = ft_strdup(ft_strchr(ptr , '=' + 1));
		// arg[1] = ft_data(ptr);
		// printf(".............  %s \n", arg[1]);
		if (arg[1][0] == '\0')
		{
			free(arg[1]);
			arg[1] = ft_strdup("+");
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
		ft_error(str, "minishell:`");
		return (1);
	}
	if (ft_isdigit(str[0]))
	{
		ft_error(str, "minishell:`");
		return (1);
	}
	// while (str[i] && (str[i] != '+' && str[i] != '='))
	while (str[i] && str[i] != '=')
	{
		if (str[i] < '0' || (str[i] >= ':' && str[i] <= '@') || (str[i] >= '['
				&& str[i] <= '^') || str[i] >= '{' || str[i] == '`')
		{
			ft_error(str, "minishell:`");
			return (1);
		}
		i++;
	}
	return (0);
}

void	export_1(t_environment **var, t_command *str, int *i)
{
	char			*ptr_1;
	char			*ptr_2;
	t_environment	*elem;
	char			**list;

	list = split_line(str->arg[*i]);
	ptr_1 = ft_strdup(list[0]);
	ptr_2 = ft_strdup(list[1]);

	// printf("***************  [%s]\n", ptr_1);
	// printf("***************  [%s]\n", ptr_2);
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


int ft_check_var(t_environment **var, t_command *str)
{
	char			*ptr_1;
	char			*ptr_2;
	t_environment	*elem;
	char			**list;
	
	if (*var == NULL)
	{
		if (str->arg[1] == NULL)
			return 1 ;
		if (str->arg[1][0] == '-')
		{
			ft_putstr_fd("invalid option\n", 2);
			g_exit_status = 2;
			return  1;
		}
		if (check_is_valid_1(str->arg[1]) == 1)
			return 1;
		list = split_line(str->arg[1]);
		ptr_1 = ft_strdup(list[0]);
		ptr_2 = ft_strdup(list[1]);
		elem = new_node(ptr_1, ptr_2);
		add_back_node(var, elem);
		return 1;
	}
	return 0;
}
void	ft_export(t_environment **var, t_command *str)
{
	int	i;

	i = 1;
	if (ft_check_var(var, str))
		return ;
	while (str->arg[i] != NULL)
	{
		if (str->arg[i][0] == '\0')
			i++;
		else
		{
			if (str->arg[1][0] == '-')
			{
				ft_putstr_fd("invalid option\n", 2);
				g_exit_status = 2;
				return ;
			}
			if (check_is_valid_1(str->arg[i]) == 1)
				return ;
			export_1(var, str, &i);
		}
	}
	affiche_export(str->arg, var);
}
