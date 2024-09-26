/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:49:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/26 12:08:56 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum_exp(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a'
			&& c <= 'z') || (c == '_') || c == '<' || c == '>');
}

void	print_export(t_environment **var)
{
	t_environment	*ptr;

	if (*var == NULL || var == NULL)
		return ;
	ptr = *var;
	while (ptr != NULL)
	{
		if (ptr->data == NULL )
			printf("declare -x %s\n", (char *)ptr->var);
		else if (ptr->data != NULL && ptr->data[0] == '='
			&& ptr->data[1] == '\0')
			printf("declare -x %s=\"\"\n", (char *)ptr->var);
		else
			printf("declare -x %s=\"%s\"\n", (char *)ptr->var,
				(char *)ptr->data);
		ptr = ptr->next;
	}
	return ;
}

// void	check_dolar_is(char *str, t_environment *var, t_command *s)
// {
// 	char	*ptr;
// 	int		i;

// 	i = 1;
// 	ptr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
// 	if (ptr == NULL)
// 		return ;
// 	if (str[0] == '$')
// 	{
// 		while (str[i])
// 		{
// 			if (!ft_isalnum_exp(str[i]))
// 			{
// 				ft_putstr_fd("not a valid identifier\n", 2);
// 				return ;
// 			}
// 			i++;
// 		}
// 	}
// 	if (s->arg[2] == NULL || s->arg[2][0] == '\0')
// 		print_export(&var);
// 	free(ptr);
// }

int	exist_redir(char *ptr)
{
	if (!ptr)
		return (0);
	if (ft_strcmp(ptr, ">") == 0)
		return (1);
	if (ft_strcmp(ptr, ">>") == 0)
		return (1);
	if (ft_strcmp(ptr, "<") == 0)
		return (1);
	return (0);
}
