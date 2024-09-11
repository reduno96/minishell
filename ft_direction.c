/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/11 13:05:29 by rel-mora         ###   ########.fr       */
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

void	ft_skip_spaces_and_quotes(t_splitor **tmp_x)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' || (*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
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

char	*ft_skip_direction(t_splitor **tmp_x, t_envarment *my_env, int *is_amb,
		int her)
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
		final = ft_double_and_sigle(tmp_x, my_env);
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G)
	{
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type == '$')
		{
			s = ft_expand((*tmp_x)->in, my_env);
			if (ft_check_ambiguous(s) == NULL && her == 0)
				return (*is_amb = 1, NULL);
			final = ft_strjoin(final, s);
			return (final);
		}
		else if ((*tmp_x) != NULL && (*tmp_x)->state == G)
			final = ft_word(tmp_x, my_env);
	}
	return (final);
}
void	ft_skip_one_quote(t_splitor **tmp_x)
{
	if ((*tmp_x) != NULL && ((*tmp_x)->type == '\'' || (*tmp_x)->type == '\"'))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_next(t_splitor **tmp_x, t_command **tmp_cmd)
{
	if ((*tmp_x) != NULL && (*tmp_x)->type == '|')
		(*tmp_x) = (*tmp_x)->next;
	if ((*tmp_cmd) != NULL)
		(*tmp_cmd) = (*tmp_cmd)->next;
	if ((*tmp_cmd) != NULL && (*tmp_x) != NULL)
		(*tmp_cmd) = (*tmp_cmd)->next;
}

int	ft_fill_redirection(t_splitor **tmp_x, t_command *tmp_cmd,
		t_envarment *my_env)
{
	char	*final;
	int		is_amb;

	final = NULL;
	is_amb = 0;
	if ((*tmp_x) != NULL && (*tmp_x)->type == '>' && (*tmp_x)->state == G)
	{
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		final = ft_skip_direction(&(*tmp_x), my_env, &is_amb, 0);
		ft_add_redir((&tmp_cmd->doc), ft_new_redir(final, '>', is_amb));
		return (1);
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->type == '<' && (*tmp_x)->state == G)
	{
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		final = ft_skip_direction(tmp_x, my_env, &is_amb, 0);
		ft_add_redir((&tmp_cmd->doc), ft_new_redir(final, '<', is_amb));
		return (1);
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->type == DREDIR_OUT
		&& (*tmp_x)->state == G)
	{
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_spaces(tmp_x);
		final = ft_skip_direction(tmp_x, my_env, &is_amb, 0);
		ft_add_redir((&tmp_cmd->doc), ft_new_redir(final, DREDIR_OUT, is_amb));
		return (1);
	}
	return (0);
}

void	ft_check_redirection(t_pre *id, t_envarment *my_env)
{
	char	*final;

	if (ft_fill_redirection(&id->tmp_x, id->tmp_cmd, my_env))
		;
	else if ((id->tmp_x != NULL && id->tmp_x->type == HERE_DOC
		&& id->tmp_x->state == G))
	{
		id->tmp_x = id->tmp_x->next;
		ft_skip_spaces(&id->tmp_x);
		final = ft_skip_direction(&id->tmp_x, my_env, 0, 1);
		printf("%s\n", final);
		ft_add_redir(&(id->tmp_cmd->doc), ft_new_redir(final, HERE_DOC, 0));
		if (id->tmp_x != NULL && id->tmp_x->state == G && ( (id->tmp_x->next != NULL && id->tmp_x->type == 32) || id->tmp_x->next == NULL))
			id->is_expand = 1;
		add_back_node_her(&(id->tmp_cmd->her), new_node_her(final, -1, id->j,
				id->is_expand));
	}
	if (id->tmp_x != NULL)
		id->tmp_x = id->tmp_x->next;
}
void	ft_fill_red(t_command **cmd, t_splitor **x, t_envarment *my_env)
{
	t_pre	id;

	id.is_expand = 0;
	id.j = 0;
	id.i = 0;
	id.tmp_cmd = *cmd;
	id.tmp_x = *x;
	while (id.tmp_cmd != NULL && id.tmp_x != NULL)
	{
		id.tmp_cmd->doc = NULL;
		id.i = 0;
		while ((id.tmp_cmd != NULL && id.tmp_x != NULL)
			&& !(id.tmp_x->state == G && id.tmp_x->type == '|'))
		{
			ft_check_redirection(&id, my_env);
			id.i++;
		}
		ft_next(&id.tmp_x, &id.tmp_cmd);
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
