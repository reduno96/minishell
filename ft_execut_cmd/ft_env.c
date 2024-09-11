/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/11 20:04:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_envarment **var)
{
	t_envarment	*ptr;

	ptr = *var;
	while (ptr)
	{
		if ( ptr != NULL && (ptr->data != NULL || ptr->data[0] == '\0'))
		{
			ptr = ptr->next;
		}
		else if (ptr->data[0] == '=' && ptr->data[1] == '\0')
		{
			printf("%s=\n", ptr->var);
			ptr = ptr->next;
		}
		else
		{
			printf("%s=%s\n", ptr->var, ptr->data);
			ptr = ptr->next;
		}
	}
}
