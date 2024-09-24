/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/24 16:58:43 by bouhammo         ###   ########.fr       */
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
		printf("type : %d | %s\n", current->type, current->store);
		current = current->next;
	}
}
void	print_redirect_here(t_here_doc *head)
{
	t_here_doc	*current;

	(void)head;
	current = head;
	while (current != NULL)
	{
		printf("type : |%s|\n", current->store);
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
	// t_command	*h;
	// i = 0;
	// h = *cmd;
	// while (h != NULL)
	// {
	// 	printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
	// 	if (h->content != NULL)
	// 	{
	// 		printf("Content :		[%s] \n", h->content);
	// 	}
	// 	if (h->arg != NULL && h->arg[0] != NULL)
	// 	{
	// 		printf("Argument :	");
	// 		i = 0; // Initialize i before using it
	// 		while (h->arg[i] != NULL)
	// 		{
	// 			printf(" [%s] ", h->arg[i]);
	// 			i++;
	// 		}
	// 	}
	// 	printf("\n");
	// 	printf("doc :		\n");
	// 	print_redirect_list(h->doc);
	// 	print_redirect_here(h->her);

	// 	printf("\n");
	// 	i = 0;
	// 	// printf("HerDoc :		\n");
	// 	// if (h->store_her != NULL && h->store_her[0] != NULL)
	// 	// 	while (h->store_her[i] != NULL)
	// 	// 	{
	// 	// 		if (h->store_her[i] == '\0')
	// 	// 			printf("____in herdoc print_________\n");
	// 	// 		printf("HerDoc ==>> %s \n\n", h->store_her[i]);
	// 	// 		i++;
	// 	// 	}
	// 	h = h->next;
	// }
}
