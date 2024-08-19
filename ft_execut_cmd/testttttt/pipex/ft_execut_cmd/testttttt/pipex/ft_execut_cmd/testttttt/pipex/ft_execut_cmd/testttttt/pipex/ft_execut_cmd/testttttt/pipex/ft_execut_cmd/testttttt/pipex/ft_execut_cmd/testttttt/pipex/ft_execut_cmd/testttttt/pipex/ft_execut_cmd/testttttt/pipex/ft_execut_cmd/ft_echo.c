/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:06:30 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/15 11:56:06 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_command *list ,char **env)
{
	int i = 1;
	int j = 0;
	bool flag = true;
	if(list->arg[1])
	{
		while (list->arg[1][i])
		{
			if(list->arg[1][0] == '-' && list->arg[1][i] == 'n')
				flag = true;
			else
			{
				flag = false;
				break;
			}
			i++;
		}	
	}
	if(flag == true)
	{
		ft_echo_flag(list);
		if(test_redir_here_doc(list) == 1)
		{
			char **new = ft_new_args(list->arg, list->doc);
			execution_cmd(list, new ,env);
		}
		return ;
	}
	i = 1;	
	while(list->arg[i])
	{
		j =0;
		while (list->arg[i][j])
		{
			write(1, &list->arg[i][j], 1);
			j++;
		}
		write(1, " ", 2);
		i++;
	}
	write(1, "\n", 1);
		if(test_redir_here_doc(list) == 1)
	{
		char **new = ft_new_args(list->arg, list->doc);
		execution_cmd(list, new ,env);
	}
}

void 	ft_echo_flag(t_command  *list)
{
	int i = 2;
	int j;
	while(list->arg[i + 1] && list->arg != NULL)
	{
		j = 0;
		while(list->arg[i][j])
		{
			write(1, &list->arg[i][j], 1);
			j++;
		}
		write(1, " ", 1);
		i++;
	}
	j = 0;
	while(list->arg[i][j] && list->arg != NULL)
	{
		write(1, &list->arg[i][j], 1);
		j++;
	}
}
