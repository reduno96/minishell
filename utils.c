/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:23:44 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/26 16:18:04 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_search(char *s, char *d)
{
    int i = 0;
    while(s[i])
    {
        if (s[i] == d[i])
            i++;
        else if(d[i] == '\0')
            return 1;
        else
            break;
    }
    return 0;
}

int ft_isspace(char c)
{
    return ((c == ' ' || c == '\t' || c == '\n'));
}