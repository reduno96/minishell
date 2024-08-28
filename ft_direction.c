/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/27 18:01:25 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirect_list(t_redirect *head)
{
	printf("I'm here in printt redirect\n");
	t_redirect	*current;

	current = head;
	while (current != NULL)
	{
		printf("Type: %d, Store: %s\n", current->type, current->store);
		current = current->next;
	}
}

int	ft_check_redir(char *arg)
{
	if (ft_search(arg, "<"))
		return (1);
	else if (ft_search(arg, ">"))
		return (1);
	else if (ft_search(arg, ">>"))
		return (1);
	else if (ft_search(arg, "<<"))
		return (1);
	return (0);
}

void	ft_check_doc(t_command **new_node)
{
	t_command	*tmp;
	int			i;

	tmp = *new_node;
	i = 0;
	(*new_node)->doc = NULL;
	while (tmp->arg[i] != NULL)
	{
		if (ft_search(tmp->arg[i], "<"))
			ft_add_redir(&(*new_node)->doc, ft_new_redir(tmp->arg[i + 1], '<'));
		else if (ft_search(tmp->arg[i], ">"))
			ft_add_redir(&(*new_node)->doc, ft_new_redir(tmp->arg[i + 1], '>'));
		else if (ft_search(tmp->arg[i], "<<"))
			ft_add_redir(&(*new_node)->doc, ft_new_redir(tmp->arg[i + 1],
					HERE_DOC));
		else if (ft_search(tmp->arg[i], ">>"))
			ft_add_redir(&(*new_node)->doc, ft_new_redir(tmp->arg[i + 1],
					DREDIR_OUT));
		i++;
	}
	print_redirect_list((*new_node)->doc);
}
