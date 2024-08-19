/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:45 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/15 18:47:44 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_cd(t_command *list)
{
	char *path ;

	if (list->arg[1] == NULL)
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
			perror("No such file or directory");
	}
	else
	{
		path = list->arg[1];
		if (chdir(path) == -1)
			perror("No such file or directory");
	}
}


