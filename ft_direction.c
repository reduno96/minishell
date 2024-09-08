/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/07 07:36:31 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirect_list(t_redirect *head)
{
	(void)head;
	/* t_redirect	*current;
	current = head;
	while (current != NULL)
	{
		current = current->next;
	} */
}

void	ft_skip_spaces_and_quotes(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' || (*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\"'))
		(*tmp_x) = (*tmp_x)->next;
}

char	*ft_check_ambiguous(char *tmp_x)
{
	if (tmp_x == NULL)
		return (NULL);
	else if (tmp_x != NULL && !ft_search(tmp_x, " "))
		return (tmp_x);
	return (tmp_x);
}

char	*ft_skip_direction(t_splitor **tmp_x, t_envarment *my_env)
{
	char	*s;
	char	*final;

	final = NULL;
	if (((*tmp_x) != NULL && (*tmp_x)->next != NULL) && (((*tmp_x)->type == '\"'
				&& (*tmp_x)->next->type == '\"') || ((*tmp_x)->type == '\''
				&& (*tmp_x)->next->type == '\'')))
		final = ft_strdup("\0");
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		while ((*tmp_x) != NULL && (*tmp_x)->state == G
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
		{
			if (((*tmp_x) != NULL && (*tmp_x)->state == G)
				&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
				(*tmp_x) = (*tmp_x)->next;
			while ((*tmp_x) != NULL && ((*tmp_x)->state == D
					|| (*tmp_x)->state == S))
			{
				if ((*tmp_x) != NULL && (*tmp_x)->state != S
					&& (*tmp_x)->type == '$')
				{
					while ((*tmp_x) != NULL && (*tmp_x)->state != S
						&& (*tmp_x)->type == '$')
					{
						s = ft_expand((*tmp_x)->in, my_env);
						final = ft_strjoin(final, s);
						(*tmp_x) = (*tmp_x)->next;
					}
				}
				else if ((*tmp_x) != NULL && (*tmp_x)->state != G)
				{
					while ((*tmp_x) != NULL && (*tmp_x)->state != G)
					{
						final = ft_strjoin(final, (*tmp_x)->in);
						(*tmp_x) = (*tmp_x)->next;
					}
				}
				else if ((*tmp_x) != NULL)
				{
					final = ft_strjoin(final, (*tmp_x)->in);
					(*tmp_x) = (*tmp_x)->next;
				}
			}
			if ((*tmp_x) != NULL && (*tmp_x)->state != S
				&& (*tmp_x)->type == '$')
			{
				s = ft_expand((*tmp_x)->in, my_env);
				final = ft_strjoin(final, s);
			}
			else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
					|| (*tmp_x)->state == S))
				final = ft_strjoin(final, (*tmp_x)->in);
			if ((*tmp_x) != NULL)
				(*tmp_x) = (*tmp_x)->next;
		}
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G)
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type == '$')
		{
			s = ft_expand((*tmp_x)->in, my_env);
			final = ft_strjoin(final, s);
			if (ft_check_ambiguous(s) == NULL)
				return (NULL);
			return (final);
		}
		else if ((*tmp_x) != NULL && (*tmp_x)->state == G
			&& (*tmp_x)->type != '$')
			return ((*tmp_x)->in);
	}
	return (final);
}
void	ft_skip_one_quote(t_splitor **tmp_x)
{
	if ((*tmp_x) != NULL && ((*tmp_x)->type == '\'' || (*tmp_x)->type == '\"'))
		(*tmp_x) = (*tmp_x)->next;
}
void	ft_fill_red(t_command **cmd, t_splitor **x, t_envarment *my_env)
{
	t_command	*tmp_cmd;
	t_splitor	*tmp_x;
	char		*final;
	int			i;
	int			j;
	int			is_expand;

	is_expand = 0;
	j = 0;
	i = 0;
	tmp_cmd = *cmd;
	tmp_x = *x;
	while (tmp_cmd != NULL && tmp_x != NULL)
	{
		tmp_cmd->doc = NULL;
		i = 0;
		while ((tmp_cmd != NULL && tmp_x != NULL) && !(tmp_x->state == G
				&& tmp_x->type == '|'))
		{
			if (tmp_x != NULL && tmp_x->type == '>' && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				final = ft_skip_direction(&tmp_x, my_env);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(final, '>'));
			}
			else if (tmp_x != NULL && tmp_x->type == '<' && tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				final = ft_skip_direction(&tmp_x, my_env);
				ft_add_redir((&tmp_cmd->doc),
					ft_new_redir(ft_check_ambiguous(final), '<'));
			}
			else if (tmp_x != NULL && tmp_x->type == DREDIR_OUT
				&& tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces(&tmp_x);
				final = ft_skip_direction(&tmp_x, my_env);
				ft_add_redir((&tmp_cmd->doc),
					ft_new_redir(ft_check_ambiguous(final), DREDIR_OUT));
			}
			else if (tmp_x != NULL && tmp_x->type == HERE_DOC
				&& tmp_x->state == G)
			{
				tmp_x = tmp_x->next;
				ft_skip_spaces_and_quotes(&tmp_x);
				ft_add_redir((&tmp_cmd->doc), ft_new_redir(tmp_x->in,
						HERE_DOC));
				if (tmp_x->state == G)
					is_expand = 1;
				add_back_node_her((&tmp_cmd->her), new_node_her(tmp_x->in, -1,
						j, is_expand));
			}
			if (tmp_x != NULL)
				tmp_x = tmp_x->next;
			i++;
		}
		if (tmp_x != NULL && tmp_x->type == '|')
			tmp_x = tmp_x->next;
		if (tmp_cmd != NULL)
			tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_x != NULL)
			tmp_cmd = tmp_cmd->next;
	}
}
void	ft_fill_store(t_command **tmp_cmd)
{
	int			i;
	t_redirect	*tmp;

	i = 0;
	(*tmp_cmd)->store_her = NULL;
	(*tmp_cmd)->len = 0;
	tmp = (*tmp_cmd)->doc;
	while (tmp != NULL)
	{
		if (tmp->type == HERE_DOC)
			(*tmp_cmd)->len++;
		tmp = tmp->next;
	}
	(*tmp_cmd)->store_her = malloc(sizeof(char *) * ((*tmp_cmd)->len + 1));
	tmp = (*tmp_cmd)->doc;
	while (tmp != NULL)
	{
		if (tmp->type == HERE_DOC)
		{
			(*tmp_cmd)->store_her[i] = ft_strdup(tmp->store);
			i++;
		}
		tmp = tmp->next;
	}
	(*tmp_cmd)->store_her[i] = NULL;
}
void	ft_fill_her(t_command **new_node)
{
	t_command	*tmp_cmd;

	tmp_cmd = *new_node;
	while (tmp_cmd != NULL)
	{
		ft_fill_store(&tmp_cmd);
		if (tmp_cmd != NULL)
			tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_cmd->is_pipe)
			tmp_cmd = tmp_cmd->next;
	}
}
