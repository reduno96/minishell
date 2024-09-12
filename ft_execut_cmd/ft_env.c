/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/12 07:59:57 by rel-mora         ###   ########.fr       */
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
			ptr = ptr->next;
		}
		else
		{
			ptr = ptr->next;
		}
	}
}
