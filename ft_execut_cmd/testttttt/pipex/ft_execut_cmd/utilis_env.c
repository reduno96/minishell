/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/09 19:20:17 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envarment  *new_node(void *var, void *data)
{
        t_envarment  *elem;

        elem = (t_envarment *)malloc(sizeof(t_envarment));
        if (!elem)
                return (NULL);
        elem->var = var;
		elem->data = data;
        elem->next = NULL;
        return (elem);
}


void    add_back_node(t_envarment **lst, t_envarment *new)
{
        t_envarment  *p;

        p = *lst;
        if (!lst || !new)
                return ;
        if (!(*lst))
        {
                *lst = new;
                return ;
        }
            while (p->next)
    {
       p=p->next;
    }
    p->next =new;
}