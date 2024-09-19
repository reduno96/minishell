/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/19 14:46:46 by rel-mora         ###   ########.fr       */
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

/* 	int			i;
	t_command	*tmp_cmd;
	i = 0;
	tmp_cmd = *cmd;
	while (tmp_cmd != NULL)
	{
		printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
		if (tmp_cmd->content != NULL)
		{
			// printf("Content :		[%s] \n", tmp_cmd->content);
		}
		if (tmp_cmd->arg != NULL && tmp_cmd->arg[0] != NULL)
		{
			printf("Argument :	");
			i = 0; // Initialize i before using it
			while (tmp_cmd->arg[i] != NULL)
			{
				printf(" [%s] ", tmp_cmd->arg[i]);
				i++;
			}
		}
		printf("\n");
		printf("doc :		\n");
		print_redirect_list(tmp_cmd->doc);
		// printf("\n");
		i = 0;
		// printf("HerDoc :		\n");
		// if (tmp_cmd->store_her != NULL && tmp_cmd->store_her[0] != NULL)
		// 	while (tmp_cmd->store_her[i] != NULL)
		// 	{
		// 		if (tmp_cmd->store_her[i] == '\0')
		// 			printf("____in herdoc print_________\n");
		// 		printf("HerDoc ==>> %s \n\n", tmp_cmd->store_her[i]);
		// 		i++;
		// 	}
		tmp_cmd = tmp_cmd->next;
	} */
}
