/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:48:18 by rel-mora          #+#    #+#             */
/*   Updated: 2024/01/10 18:01:42 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;
	char	*s_one;
	char	*s_two;
	int		i;
	int		j;

	s_one = (char *)s1;
	s_two = (char *)s2;
	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	d = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (s_one[i])
		d[j++] = s_one[i++];
	i = 0;
	while (s_two[i])
		d[j++] = s_two[i++];
	d[j] = '\0';
	return (d);
}
