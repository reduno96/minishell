/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/15 11:30:04 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_command *list)
{
	int 	i;
	char	*path;

	i = 0;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("");
		g_exit_status =1;
		return ;
	}
	// printf("---------------------   %s \n", list->arg[i + 1] );
	if( list->arg[1] != NULL && list->arg[1][0] == '-' && list->arg[1][1] != '\0')
	{
		ft_putstr_fd("pwd", 2);
		ft_putstr_fd(": invalid option\n", 2);
		g_exit_status =1;
		return;
	}
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	free(path);
	g_exit_status = 0;
}
