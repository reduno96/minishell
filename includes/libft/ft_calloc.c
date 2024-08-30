/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 02:12:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/30 08:12:06 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t size)
{
	size_t	i;
	char	*src;

	i = 0;
	src = malloc(size);
	if (src == NULL)
		return (NULL);
	while (i < size)
	{
		src[i] = '\0';
		i++;
	}
	return (src);
}
