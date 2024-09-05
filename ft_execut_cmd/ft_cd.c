/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:45 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/29 19:27:44 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(t_command *list)
{
	char	*path;

	if (list->arg[1] == NULL)
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
			perror("");
	}
	else
	{
		path = list->arg[1];
		if (path[0] == '~')
			path = getenv("HOME");
		if (ft_strcmp(path, "--") == 0)
			path = getenv("HOME");
		if (path[0] == '-' && path[1] == '\0')
		{
			path = getenv("OLDPWD");
			printf("%s\n", path);
		}
		if (chdir(path) == -1)
			printf("bash: cd: %s: No such file or directory\n", path);
	}
}
