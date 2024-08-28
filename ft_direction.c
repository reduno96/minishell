/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/28 16:25:18 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirect_list(t_redirect *head)
{
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

void	ft_fill_red(t_command **cmd, t_splitor **x)
{
	t_command	*tmp_cmd;
	t_splitor	*tmp_x;

	tmp_cmd = *cmd;
	tmp_x = *x;
	while (tmp_cmd != NULL)
	{
		while (tmp_cmd != NULL && tmp_x != NULL && tmp_x->state == G
			&& tmp_x->type != '|')
		{
			if (tmp_x->type == '<' && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in, '<'));
			}
			else if (tmp_x->type == '>' && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in, '>'));
			}
			else if (tmp_x->type == DREDIR_OUT && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in,
						DREDIR_OUT));
			}
			else if (tmp_x->type == HERE_DOC && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in,
						HERE_DOC));
			}
			tmp_x = tmp_x->next;
		}
		if (tmp_x != NULL && tmp_x->type == '|')
			tmp_x = tmp_x->next;
		if (tmp_cmd != NULL)
			tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_cmd->is_pipe)
			tmp_cmd = tmp_cmd->next;
	}
}

void	ft_fill_her(t_command **new_node)
{
	t_command	*tmp_cmd;
	t_redirect	*tmp;
	int			i;

	tmp_cmd = *new_node;
	i = 0;
	while (tmp_cmd != NULL)
	{
		(*new_node)->len = 0;
		tmp = (*new_node)->doc;
		while (tmp != NULL)
		{
			if (tmp->type == HERE_DOC)
				(*new_node)->len++;
			tmp = tmp->next;
		}
		(*new_node)->store_her = malloc(sizeof(char *) * (*new_node)->len + 1);
		tmp = (*new_node)->doc;
		while (tmp != NULL)
		{
			if (tmp->type == HERE_DOC)
			{
				(*new_node)->store_her[i] = ft_strdup(tmp->store);
				i++;
			}
			tmp = tmp->next;
		}
		(*new_node)->store_her[i] = NULL;
		tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_cmd->is_pipe)
			tmp_cmd = tmp_cmd->next;
	}
}
