/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:49 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/19 15:22:28 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void 	ft_env( t_envarment *var)
{
	t_envarment *ptr;
	ptr = var;
	while (ptr)
	{
		printf("%s   {***}    %s \n", ptr->var, ptr->data);
		ptr=ptr->next;
	}
}
