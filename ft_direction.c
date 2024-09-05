/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_direction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:24:52 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/05 18:24:07 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redirect_list(t_redirect *head)
{
	t_redirect	*current;

	current = head;
	while (current != NULL)
	{
		// printf("Type: %d, Store: %s\n", current->type, current->store);
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

char	*ft_check_ambiguous(char *tmp_x)
{
	if (tmp_x == NULL)
	{
		// printf("________1\n");
		return (NULL);
	}
	else if (tmp_x != NULL && !ft_search(tmp_x, " "))
	{
		// printf("________3\n");
		return (tmp_x);
	}
	// printf("The end of the function \n");
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
			// printf("___1________Dire__%s___\n", (*tmp_x)->in);
			if (((*tmp_x) != NULL && (*tmp_x)->state == G)
				&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
				(*tmp_x) = (*tmp_x)->next;
			// printf("___2________Dire__%s___\n", (*tmp_x)->in);
			while ((*tmp_x) != NULL && ((*tmp_x)->state == D
					|| (*tmp_x)->state == S))
			{
				// printf("spances\n");
				if ((*tmp_x) != NULL && (*tmp_x)->state != S
					&& (*tmp_x)->type == '$')
				{
					while ((*tmp_x) != NULL && (*tmp_x)->state != S
						&& (*tmp_x)->type == '$')
					{
						s = ft_expand((*tmp_x)->in, my_env);
						final = ft_strjoin(final, s);
						free(s);
						(*tmp_x) = (*tmp_x)->next;
					}
				}
				else if ((*tmp_x) != NULL && (*tmp_x)->state != G)
				{
					while ((*tmp_x) != NULL && (*tmp_x)->state != G)
					{
						// printf("|%s|\n", (*tmp_x)->in);
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
				free(s);
			}
			else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
					|| (*tmp_x)->state == S))
				final = ft_strjoin(final, (*tmp_x)->in);
			if ((*tmp_x) != NULL)
				(*tmp_x) = (*tmp_x)->next;
		}
	}
	else if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type == -1)
	{
		// printf("____________HI_in skip direction ");
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type == '$')
		{
			s = ft_expand((*tmp_x)->in, my_env);
			final = ft_strjoin(final, (*tmp_x)->in);
			if (ft_check_ambiguous(s) == NULL)
			{
				free(s);
				return (NULL);
			}
			else
			{
				free(s);
				return (final);
			}
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
	// if ((*x) == NULL || x == NULL || cmd == NULL)
	// 	return ;
	tmp_cmd = *cmd;
	tmp_x = *x;
	// while (1)
	// 	;
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
				// ft_skip_one_quote(&tmp_x);
				final = ft_skip_direction(&tmp_x, my_env);
				ft_add_redir((&tmp_cmd->doc),
					ft_new_redir(ft_check_ambiguous(final), '>'));
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
				j++; // printf("in else if condition  \n");
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
		{
			// printf("tmp++++++>%s\n", tmp_cmd->content);
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
	while (tmp_cmd != NULL)
	{
		i = 0;
		// printf(".........................................\n\n");
		tmp_cmd->store_her = NULL;
		tmp_cmd->len = 0;
		tmp = tmp_cmd->doc;
		while (tmp != NULL)
		{
			if (tmp->type == HERE_DOC)
				tmp_cmd->len++;
			tmp = tmp->next;
		}
		// printf("tmp_cmd->len = %d\n", tmp_cmd->len);
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
		if (tmp_cmd != NULL)
			tmp_cmd = tmp_cmd->next;
		if (tmp_cmd != NULL && tmp_cmd->is_pipe)
			tmp_cmd = tmp_cmd->next;
	}
}
