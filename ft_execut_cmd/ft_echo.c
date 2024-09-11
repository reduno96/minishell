/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 09:06:30 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/11 18:35:18 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	complet_function(t_command *list, int k, bool flag)
{
	if (test_redir_here_doc(list) == 1)
	{
		hundle_redirections(list);
		execution_cmd(list, list->arg);
	}
	while (list->arg[k])
	{
		ft_putstr_fd(list->arg[k] , 1);
		if (list->arg[k + 1] != NULL)
			ft_putstr_fd(" ", 1);
		k++;
	}
	if (!flag || k == 1)
		ft_putstr_fd("\n" ,1);
}

void	ft_echo(t_command *list )
{
	int		k;
	bool	flag;
	bool	flag_dolar;
	int		i;

	k = 1;
	flag = false;
	flag_dolar = false;
	while (list->arg[k])
	{
		if (list->arg[k][0] == '-' && list->arg[k][1] != '\0')
		{
			i = 1;
			while (list->arg[k][i] == 'n')
				i++;
			if (list->arg[k][i] != '\0')
				break ;
			flag = true;
		}
		else
			break ;
		k++;
	}
	complet_function(list, k, flag);
}
