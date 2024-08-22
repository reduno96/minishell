/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:01 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/21 19:57:09 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	 ft_pwd(t_command *list)
{
	(void)list;
	char *path ;
			path = getcwd(NULL, 0);
			if(path == NULL)
				return 0;
			printf("%s\n", path);	

	return (1);
}
