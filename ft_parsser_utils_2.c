/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:12 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/02 18:03:41 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_spaces(t_splitor **tmp_x)
{
	// printf("Skiip spaces\n");
	while ((*tmp_x) != NULL && (*tmp_x)->type == ' ')
		(*tmp_x) = (*tmp_x)->next;
}
void	ft_skip_spaces_in_count(t_splitor **tmp_x)
{
	// printf("________in skip_cout\n");
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		printf("HI IM IN SKIP SPACES\n\n");
		(*tmp_x) = (*tmp_x)->next;
	}
	// printf("_____ABC____\n");
	// printf("====%c===%s===\n", (*tmp_x)->state, (*tmp_x)->in);
	ft_skip_spaces(tmp_x);
	while ((*tmp_x) != NULL && (*tmp_x)->state != G)
	{
		// printf("============================\n");
		(*tmp_x) = (*tmp_x)->next;
	}
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_spaces_in_count__2(t_splitor **tmp_x)
{
	// printf("________in skip_cout\n");
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		// printf("HI IM IN SKIP SPACES\n\n");
		(*tmp_x) = (*tmp_x)->next;
	}
	// printf("_____ABC____\n");
	// printf("====%c===%s===\n", (*tmp_x)->state, (*tmp_x)->in);
	ft_skip_spaces(tmp_x);
	while ((*tmp_x) != NULL && (*tmp_x)->state != G)
	{
		// printf("============================\n");
		(*tmp_x) = (*tmp_x)->next;
	}
	while ((*tmp_x) != NULL && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\"'))
		(*tmp_x) = (*tmp_x)->next;
}

void	ft_skip_quote(t_splitor **tmp_x, int *i, t_command **new_node)
{
	// printf("HI I'M IN SKIP QUOTE FUNCTION \n");
	// printf("__%s_\n", (*tmp_x)->in);
	(*tmp_x) = (*tmp_x)->next;
	if (((*tmp_x) != NULL && (*tmp_x)->state == G) && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
	}
}
/* while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		printf("in while loop__%s_\n", (*tmp_x)->in);
		while (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		while ((*tmp_x) != NULL && (*tmp_x)->state != S
			&& (*tmp_x)->type == '$')
		{
			printf("red\n");
			s = ft_expand((*tmp_x)->in, my_env);
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
			if ((*tmp_x) != NULL)
				(*tmp_x) = (*tmp_x)->next;
				while (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		}
		if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type == -1)
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
					(*tmp_x)->in);
		if ((*tmp_x) != NULL)
			(*tmp_x) = (*tmp_x)->next;
	} */
void	ft_skip_general(t_splitor **tmp_x, int *i, t_command **new_node,
		t_envarment *my_env)
{
	char	*s;

	while ((*tmp_x) != NULL && (*tmp_x)->state == G && ((*tmp_x)->type == '\"'
			|| (*tmp_x)->type == '\''))
	{
		// printf("___1_____________\n");
		if (((*tmp_x) != NULL && (*tmp_x)->state == G)
			&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
			(*tmp_x) = (*tmp_x)->next;
		// printf("in while skip general ****%s\n", (*tmp_x)->in);
		while ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
		{
			if ((*tmp_x) != NULL && (*tmp_x)->state != S
				&& (*tmp_x)->type == '$')
			{
				s = ft_expand((*tmp_x)->in, my_env);
				(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
			}
			else if ((*tmp_x) != NULL)
			{
				(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
						(*tmp_x)->in);
				// printf("________Hi_i'm infher\n");
			}
			(*tmp_x) = (*tmp_x)->next;
		}
		if ((*tmp_x) != NULL && (*tmp_x)->state != S && (*tmp_x)->type == '$')
		{
			s = ft_expand((*tmp_x)->in, my_env);
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
		}
		else if ((*tmp_x) != NULL && ((*tmp_x)->state == D
				|| (*tmp_x)->state == S))
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
					(*tmp_x)->in);
		if ((*tmp_x) != NULL)
			(*tmp_x) = (*tmp_x)->next;
	}
}
void	ft_double_and_sigle(t_splitor **tmp_x, int *i, t_command **new_node,
		t_envarment *my_env)
{
	char	*s;

	while ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$'))
		{
			s = ft_expand((*tmp_x)->in, my_env);
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
		}
		else if ((*tmp_x) != NULL)
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
					(*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		if ((*tmp_x) != NULL && ((*tmp_x)->state != S && (*tmp_x)->type == '$'))
		{
			s = ft_expand((*tmp_x)->in, my_env);
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
			(*tmp_x) = (*tmp_x)->next;
		}
		ft_skip_general(tmp_x, i, new_node, my_env);
	}
	(*i)++;
	(*new_node)->arg[*i] = NULL;
	(*new_node)->next = NULL;
}

void	ft_general_command(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	char	*s;

	s = NULL;
	while ((*tmp_x) != NULL && ((*tmp_x)->state == G && (*tmp_x)->type != ' '
			&& ((*tmp_x)->type == '$' || !ft_condition((*tmp_x)))))
	{
		if ((*tmp_x)->type == '$')
		{
			s = ft_expand((*tmp_x)->in, my_env);
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i], s);
		}
		else
			(*new_node)->arg[*i] = ft_strjoin((*new_node)->arg[*i],
					(*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
		ft_skip_general(tmp_x, i, new_node, my_env);
	}
	(*i)++;
	(*new_node)->arg[*i] = NULL;
	(*new_node)->next = NULL;
	// printf("The End of the general_command function\n");
}
void	ft_neuter_cmd(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	// printf("HI I'M IN NEUTER FUNCTION \n");
	// printf("__%s_\n", (*tmp_x)->in);
	if ((*tmp_x) != NULL && (*tmp_x)->state == G && (*tmp_x)->type != '\"'
		&& (*tmp_x)->type != '\'' && (*tmp_x)->type != '|')
		ft_general_command(new_node, i, tmp_x, my_env);
	else if ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
		ft_double_and_sigle(tmp_x, i, new_node, my_env);
	else if (((*tmp_x) != NULL && (*tmp_x)->state == G)
		&& ((*tmp_x)->type == '\"' || (*tmp_x)->type == '\''))
		ft_skip_quote(tmp_x, i, new_node);
	else if ((*tmp_x) != NULL)
		(*tmp_x) = (*tmp_x)->next;
}
void	ft_skip_not_word(t_splitor **tmp_x, t_envarment *my_env)
{
	(void)my_env;
	// printf("\nHI im in ficton skip not word\n\n");
	if ((*tmp_x)->type == '<' || (*tmp_x)->type == '>'
		|| (*tmp_x)->type == DREDIR_OUT || (*tmp_x)->type == HERE_DOC)
	{
		// printf("_*_**___%s____\n", (*tmp_x)->in);
		// printf("HI im in ficton skip not word\n\n");
		(*tmp_x) = (*tmp_x)->next;

		ft_skip_spaces(tmp_x);
		// printf("_*_**___%s____\n", (*tmp_x)->in);
		ft_skip_spaces_in_count__2(tmp_x);
		if ((*tmp_x) != NULL)
			(*tmp_x) = (*tmp_x)->next;
	}
	printf("The End skip not word\n");
}
void	ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x,
		t_envarment *my_env)
{
	while ((*tmp_x) != NULL && !((*tmp_x)->type == '|' && (*tmp_x)->state == G))
	{
		// printf("HI IM IN ft_not_pipe\n");
		// printf("__**%s***_\n", (*tmp_x)->in);
		if ((*tmp_x) != NULL && ((*tmp_x)->type != -1 && (*tmp_x)->type != '$'))
			ft_skip_not_word(tmp_x, my_env);
		if ((*tmp_x) != NULL && !((*tmp_x)->type == ' '
				&& (*tmp_x)->state == G))
			ft_neuter_cmd(new_node, i, tmp_x, my_env);
		if ((*tmp_x) != NULL && ((*tmp_x)->type == ' ' && (*tmp_x)->state == G))
			ft_skip_spaces(tmp_x);
	}
	if ((*tmp_x) != NULL && (*tmp_x)->type == '$' && (*tmp_x)->state != S)
	{
		// printf("HI IM IN ft_not_pipe\n");
		(*new_node)->arg[*i] = ft_expand((*tmp_x)->in, my_env);
		(*tmp_x) = (*tmp_x)->next;
		(*i)++;
		(*new_node)->arg[*i] = NULL;
		(*new_node)->next = NULL;
	}
	// printf(" ft_not_pipe\n\n");
}
