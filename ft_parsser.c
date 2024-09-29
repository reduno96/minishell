/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/29 10:54:40 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirect_list(t_redirect *head)
{
	t_redirect	*current;

	(void)head;
	current = head;
	while (current != NULL)
	{
		printf("2\n");
		printf("type : %d | %s\n", current->type, current->store);
		printf("type : %d \n", current->is_amb);
		current = current->next;
	}
}

void	ft_command(t_splitor **x, t_command **cmd, t_environment *my_env)
{
	t_splitor	*tmp_x;
	t_command	**tmp_cmd;

	tmp_cmd = cmd;
	tmp_x = *x;
	while (tmp_x != NULL)
		ft_add_command(cmd, ft_new_command(&tmp_x, my_env));
	ft_fill_red(tmp_cmd, x, my_env);
}
