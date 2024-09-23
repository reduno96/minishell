/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/23 13:28:35 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_command(t_splitor **x, t_command **cmd, t_envarment *my_env)
{
	t_splitor	*tmp_x;
	t_command **tmp_cmd;

	tmp_cmd = cmd;
	tmp_x = *x;
	while (tmp_x != NULL)
	{	ft_add_command(cmd, ft_new_command(&tmp_x, my_env));
		// printf("%d\n", ft_len_arg((*cmd)->arg));
	}


	ft_fill_red(tmp_cmd, x, my_env);

	// system("leaks minishell");
	// ft_fill_her(cmd);
		/* int			i;
	t_command	*tmp;
	i = 0;
	tmp = *cmd;
	while (tmp != NULL)
	{
		printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
		if (tmp->content != NULL)
		{
			printf("Content :		[%s] \n", tmp->content);
		}
		if (tmp->arg != NULL && tmp->arg[0] != NULL)
		{
			printf("Argument :	");
			i = 0; // Initialize i before using it
			while (tmp->arg[i] != NULL)
			{
				printf(" [%s] ", tmp->arg[i]);
				i++;
			}
		}
		printf("\n");
		printf("doc :		\n");
		// print_redirect_list(tmp->doc);
		// printf("\n");
		i = 0;
		// printf("HerDoc :		\n");
		// if (tmp->store_her != NULL && tmp->store_her[0] != NULL)
		// 	while (tmp->store_her[i] != NULL)
		// 	{
		// 		if (tmp->store_her[i] == '\0')
		// 			printf("____in herdoc print_________\n");
		// 		printf("HerDoc ==>> %s \n\n", tmp->store_her[i]);
		// 		i++;
		// 	}
		tmp = tmp->next;
	} */
}
