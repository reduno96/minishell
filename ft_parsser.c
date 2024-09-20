/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/20 09:47:28 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_command(t_splitor **x, t_command **cmd, t_envarment *my_env)
{
	int			count;
	t_splitor	*tmp_x;

	tmp_x = *x;
	while (tmp_x != NULL)
	{
		count = 0;
		ft_count_parameters(tmp_x, &count);
		// printf("==>%d\n", count);
		ft_add_command(cmd, ft_new_command(count, &tmp_x, my_env));
	}
	ft_fill_red(cmd, x, my_env);
	ft_fill_her(cmd);
}
