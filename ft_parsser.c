/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/19 19:33:22 by rel-mora         ###   ########.fr       */
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
		(*tmp) = (*tmp)->next;
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
		while (tmp != NULL && !(tmp->type == '|' && tmp->state == G))
		{
			ft_skip_spaces(&tmp);
			if (tmp != NULL && tmp->state == G && tmp->type != '\"'
				&& tmp->type != '\'' && tmp->type != '|')
			{
				(*count)++;
				tmp = tmp->next;
			}
			else if (tmp != NULL && (tmp->state == D || tmp->state == S))
				ft_count_d_s(&tmp, count);
			else if (tmp != NULL && tmp->type != '|')
				tmp = tmp->next;
		}
	}
}

void	ft_command(t_splitor **x, t_command **cmd)
{
	int			count;
	t_splitor	*tmp_x;
	t_command	*tmp_cmd;
	int			i;
	int			l;

	i = 0;
	tmp_x = *x;
	while (tmp_x != NULL)
	{
		count = 0;
		ft_count_parameters(tmp_x, &count);
		printf("Count: %d\n", count);
		ft_add_command(cmd, ft_new_command(count, &tmp_x));
	}
	tmp_cmd = *cmd;
	i = 0;
	l = 0;
	while (tmp_cmd != NULL)
	{
		i = 0;
		printf("\nCommand  <----------------------------------> \n");
		printf("Content : %s \n", tmp_cmd->content);
		if (tmp_cmd->arg[i] != NULL)
			printf("Argument : ");
		while (tmp_cmd->arg[i] != NULL)
		{
			printf(" [%s] ", tmp_cmd->arg[i]);
			i++;
		}
		printf("\n");
		printf("doc:\n");
		print_redirect_list(tmp_cmd->doc);
		printf("\n");
		while (tmp_cmd->store_her[l] != NULL)
		{
			printf("store: %s\n", tmp_cmd->store_her[l]);
			l++;
		}
		l = 0;
		tmp_cmd = tmp_cmd->next;
	}
}
// while (tmp_cmd != NULL)
// {
// 	printf("cmd ------------------<><><><>---------------------- \n");
// 	printf("content: %s \n", tmp_cmd->content);
// 	if (tmp_cmd->arg[i] != NULL)
// 		printf("argument: ");
// 	while (tmp_cmd->arg[i] != NULL)
// 	{
// 		printf(" %s ", tmp_cmd->arg[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	printf("t_command ----> doc:\n");
// 	printf("dir_in: %d\n", tmp_cmd->doc->dir_in);
// 	printf("dir_out: %d\n", tmp_cmd->doc->dir_out);
// 	printf("rdir: %d\n", tmp_cmd->doc->rdir);
// 	printf("doc_here: %d\n", tmp_cmd->doc->doc_here);
// 	i = 0;
// 	printf("///////////////////////////////////////////////////////////n\n");
// 	// while (tmp_cmd->doc->store[i] != NULL)
// 	// {
// 	// 	printf("store: %s\n", tmp_cmd->doc->store[i]);
// 	// 	i++;
// 	// }

// 	tmp_cmd = tmp_cmd->next;
// }