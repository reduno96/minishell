/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/24 19:08:20 by bouhammo         ###   ########.fr       */
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
		current = current->next;
	}
}

void	ft_command(t_splitor **x, t_command **cmd, t_environment *my_env)
{
	t_splitor	*tmp_x;
	t_command **tmp_cmd;

	tmp_cmd = cmd;
	tmp_x = *x;
	while (tmp_x != NULL)
		ft_add_command(cmd, ft_new_command(&tmp_x, my_env));
	ft_fill_red(tmp_cmd, x, my_env);

// int			i;
// 	t_command	*j;
// 	i = 0;
// 	j = *cmd;
// 	while (j != NULL)
// 	{
// 		printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
// 		if (j->content != NULL)
// 		{
// 			printf("Content :		[%s] \n", j->content);
// 		}
// 		if (j->arg != NULL && j->arg[0] != NULL)
// 		{
// 			printf("Argument :	");
// 			i = 0; // Initialize i before using it
// 			while (j->arg[i] != NULL)
// 			{
// 				printf(" [%s] ", j->arg[i]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 		printf("doc :		\n");
// 		print_redirect_list(j->doc);
// 		// printf("\n");
// 		i = 0;
// 		// printf("HerDoc :		\n");
// 		// if (j->store_her != NULL && j->store_her[0] != NULL)
// 		// 	while (j->store_her[i] != NULL)
// 		// 	{
// 		// 		if (j->store_her[i] == '\0')
// 		// 			printf("____in herdoc print_________\n");
// 		// 		printf("HerDoc ==>> %s \n\n", j->store_her[i]);
// 		// 		i++;
// 		// 	}
// 		j = j->next;
// 	}
}