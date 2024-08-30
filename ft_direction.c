/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/29 23:57:40 by rel-mora         ###   ########.fr       */
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

void	ft_skip_spaces_and_quotes(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' || (*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\"'))
		(*tmp_x) = (*tmp_x)->next;
}
void	ft_fill_red(t_command **cmd, t_splitor **x)
{
	t_command	*tmp_cmd;
	t_splitor	*tmp_x;

	// if ((*x) == NULL || x == NULL || cmd == NULL)
	// 	return ;
	tmp_cmd = *cmd;
	printf("jjjjjjjjjjjjjjjjjjjjjjjjjjj\n");
	tmp_x = *x;
	// while (1)
	// 	;
	// printf("tmp++++++>%s\n", tmp_cmd->content);
	while (tmp_cmd != NULL)
	{
		tmp_cmd->doc = NULL;
		printf("in function fill redirection \n");
		while (tmp_cmd != NULL && tmp_x != NULL && tmp_x->state == G
			&& tmp_x->type != '|')
		{
			if (tmp_x != NULL && tmp_x->type == '<' && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces_and_quotes(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in, '<'));
			}
			else if (tmp_x != NULL && tmp_x->type == '>' && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces_and_quotes(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in, '>'));
			}
			else if (tmp_x != NULL && tmp_x->type == DREDIR_OUT
				&& tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces_and_quotes(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in,
						DREDIR_OUT));
			}
			else if (tmp_x != NULL && tmp_x->type == HERE_DOC
				&& tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces_and_quotes(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in,
						HERE_DOC));
				printf("in else if condition  \n");
			}
			if (tmp_x != NULL)
				tmp_x = tmp_x->next;
		}
		if (tmp_x != NULL && tmp_x->type == '|')
			tmp_x = tmp_x->next;
		if (tmp_cmd != NULL)
			tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_x != NULL)
		{
			printf("tmp++++++>%s\n", tmp_cmd->content);
			tmp_cmd = tmp_cmd->next;
		}
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
		tmp_cmd->store_her = NULL;
		tmp_cmd->len = 0;
		tmp = tmp_cmd->doc;
		while (tmp != NULL)
		{
			if (tmp->type == HERE_DOC)
				tmp_cmd->len++;
			tmp = tmp->next;
		}
		tmp_cmd->store_her = malloc(sizeof(char *) * (tmp_cmd->len + 1));
		tmp = tmp_cmd->doc;
		while (tmp != NULL)
		{
			if (tmp->type == HERE_DOC)
			{
				tmp_cmd->store_her[i] = ft_strdup(tmp->store);
				i++;
			}
			tmp = tmp->next;
		}
		tmp_cmd->store_her[i] = NULL;
		tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_cmd->is_pipe)
			tmp_cmd = tmp_cmd->next;
	}
}
