/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/02 18:03:16 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_command(t_splitor *tmp_x)
{
	if (tmp_x != NULL && tmp_x->state == G && tmp_x->type != '\"'
		&& tmp_x->type != '\'' && tmp_x->type != '|')
		return (1);
	else if (tmp_x != NULL && (tmp_x->state == D || tmp_x->state == S)
		&& tmp_x->type != '|')
		return (1);
	else if (tmp_x != NULL && (tmp_x->state == D || tmp_x->state == S))
		return (1);
	return (0);
}

void	ft_count_d_s(t_splitor **tmp, int *count)
{
	while ((*tmp) != NULL && ((*tmp)->state == D || (*tmp)->state == S))
	{
		if ((*tmp) != NULL)
			(*tmp) = (*tmp)->next;
		while ((*tmp) != NULL && (*tmp)->state == G && ((*tmp)->type == '\"'
				|| (*tmp)->type == '\''))
		{
			while (((*tmp) != NULL && (*tmp)->state == G)
				&& ((*tmp)->type == '\"' || (*tmp)->type == '\''))
				(*tmp) = (*tmp)->next;
			if ((*tmp) != NULL)
				(*tmp) = (*tmp)->next;
		}
		if ((*tmp) != NULL)
			(*tmp) = (*tmp)->next;
	}
	(*count)++;
	printf("***Count_in_double_and single : %d\n", *count);
}

void	ft_count_general(t_splitor **tmp, int *count)
{
	if ((*tmp) != NULL)
		(*tmp) = (*tmp)->next;
	while ((*tmp) != NULL && (*tmp)->state == G && ((*tmp)->type == '\"'
			|| (*tmp)->type == '\''))
	{
		while (((*tmp) != NULL && (*tmp)->state == G) && ((*tmp)->type == '\"'
				|| (*tmp)->type == '\''))
			(*tmp) = (*tmp)->next;
		if ((*tmp) != NULL)
			(*tmp) = (*tmp)->next;
	}
	(*count)++;
}

void	ft_count_parameters(t_splitor *tmp_x, int *count)
{
	t_splitor	*tmp;

	tmp = tmp_x;
	if (tmp != NULL && tmp->type == '|' && tmp->state == G)
		(*count)++;
	else if (tmp != NULL)
	{
		ft_skip_spaces_in_count(&tmp);
		while (tmp != NULL && !(tmp->type == '|' && tmp->state == G))
		{
			if (tmp->type == '<' || tmp->type == '>' || tmp->type == DREDIR_OUT
				|| tmp->type == HERE_DOC)
			{
				tmp = tmp->next;
				ft_skip_spaces_in_count(&tmp);
				if (tmp != NULL)
					tmp = tmp->next;
				printf("count of %d count\n", *count);
			}
			else if ((tmp) != NULL && (tmp)->state == G && ((tmp)->type != '\"'
					&& (tmp)->type != '\'') && (tmp)->type != ' ')
				ft_count_general(&tmp, count);
			else if (tmp != NULL && (tmp->state == D || tmp->state == S))
				ft_count_d_s(&tmp, count);
			else if (tmp != NULL && tmp->type != '|')
				tmp = tmp->next;
		}
	}
}

void	ft_command(t_splitor **x, t_command **cmd, t_envarment *my_env)
{
	int			count;
	t_splitor	*tmp_x;
	t_command	*tmp_cmd;
	int			i;

	// cmd = NULL;
	tmp_x = *x;
	tmp_cmd = *cmd;
	// printf(">>>>>>>>>>>>>>>>>>HIII>>>>>>>>>>>>>>>>\n");
	while (tmp_x != NULL)
	{
		count = 0;
		ft_count_parameters(tmp_x, &count);
		printf("Count: %d\n", count);
		ft_add_command(cmd, ft_new_command(count, &tmp_x, my_env));
	}
	ft_fill_red(cmd, x, my_env);
	ft_fill_her(cmd);
	i = 0;
	tmp_cmd = *cmd;
	while (tmp_cmd != NULL)
	{
		printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
		if (tmp_cmd->content != NULL)
		{
			printf("Content :		%s \n", tmp_cmd->content);
		}
		if (tmp_cmd->arg != NULL && tmp_cmd->arg[0] != NULL)
		{
			printf("Argument :	");
			i = 0; // Initialize i before using it
			while (tmp_cmd->arg[i] != NULL)
			{
				printf(" [%s] ", tmp_cmd->arg[i]);
				i++;
			}
		}
		printf("\n");
		printf("doc :		\n");
		print_redirect_list(tmp_cmd->doc);
		printf("\n");
		i = 0;
		printf("HerDoc :		\n");
		if (tmp_cmd->store_her != NULL && tmp_cmd->store_her[0] != NULL)
			while (tmp_cmd->store_her[i] != NULL)
				printf("HerDoc ==>> %s \n\n", tmp_cmd->store_her[i++]);
		tmp_cmd = tmp_cmd->next;
	}
}
