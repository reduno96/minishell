/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:00:47 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/28 09:22:15 by rel-mora         ###   ########.fr       */
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
		printf("__________1____\n");
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
void	ft_fill_her(t_command **new_node)
{
	t_redirect	*tmp;
	int			i;

	i = 0;
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
			else if (tmp_x->type == DREDIR_OUT && tmp_x->state == G)
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
	tmp_x = *x;
	tmp_cmd = *cmd;
	ft_fill_red(cmd, x);
	tmp_cmd = *cmd;
	ft_fill_her(cmd);
	tmp_cmd = *cmd;
	i = 0;
	while (tmp_cmd != NULL)
	{
		i = 0;
		printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
		printf("Content :		%s \n", tmp_cmd->content);
		if (tmp_cmd->arg[i] != NULL)
			printf("Argument :	");
		while (tmp_cmd->arg[i] != NULL)
		{
			printf(" [%s] ", tmp_cmd->arg[i]);
			i++;
		}
		printf("\n");
		print_redirect_list(tmp_cmd->doc);
		tmp_cmd = tmp_cmd->next;
	}
	// print_redirect_list(tmp_cmd->doc);
	// tmp_cmd = tmp_cmd->next;
	// printf("__________HI_IM _________%s_________\n", tmp_cmd->arg[0]);
	// tmp_cmd = tmp_cmd->next;
	// printf("__________HI_2_________%s_________\n", tmp_cmd->arg[0]);
	// tmp_cmd = tmp_cmd->next;
	// printf("HIII in \n");
	// printf("__________HI_3 _________%s_________\n", tmp_cmd->content);
	// while (1)
	// ;
	// print_redirect_list(tmp_cmd->doc);
	// i = 0;
	// (void)l;
	// tmp_cmd = *cmd;
	// while (tmp_cmd != NULL)
	{
		// printf("\033[0;32m\n\t++++++++++++++   Command   ++++++++++++++++\n\033[0m");
		// printf("Content :		%s \n", tmp_cmd->content);
		// if (tmp_cmd->arg[i] != NULL)
		// 	printf("Argument :	");
		// i = 0;
		// while (tmp_cmd->arg[i] != NULL)
		// {
		// 	printf(" [%s] ", tmp_cmd->arg[i]);
		// 	i++;
		// }
		// i = 0;
		// printf("\n");
		// printf("doc :		\n");
		// print_redirect_list(tmp_cmd->doc);
		// printf("\n");
		// l = 0;
		// while (tmp_cmd->store_her[l] != NULL)
		// {
		// 	printf("len  = %d     store:   %s\n", tmp_cmd->len,
		// 		tmp_cmd->store_her[l]);
		// 	l++;
		// }
		// l = 0;
		// if (tmp_cmd != NULL)
		// tmp_cmd = tmp_cmd->next;
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