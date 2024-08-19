/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/19 14:03:10 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_pwd(t_command *list)
{
	(void)list;
	char *path ;
			path = getcwd(NULL, 0);
			if(path == NULL)
				return ;
			printf("%s\n", path);	
}
