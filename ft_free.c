/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:05:17 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/23 15:07:16 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lexer(t_splitor **x)
{
	t_splitor	*tmp;

	while (*x != NULL)
	{
		tmp = *x;
		*x = (*x)->next;
		if (tmp->in != NULL)
		{
			free(tmp->in);
			tmp->in = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_split(char **list)
{
	int	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list[j] != NULL)
	{
		free(list[j]);
		j++;
	}
	free(list);
	list = NULL;
}

void	ft_free_argment(char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return ;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
	free(arg);
	arg = NULL;
}

void	ft_free_doc(t_redirect **doc)
{
	t_redirect	*tmp;

	while (*doc != NULL)
	{
		tmp = *doc;
		*doc = (*doc)->next;
		if (tmp->store != NULL)
		{
			free(tmp->store);
			tmp->store = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_her(t_here_doc **her)
{
	t_here_doc	*tmp;

	while (*her != NULL)
	{
		tmp = *her;
		*her = (*her)->next;
		if (tmp->heredoc_file != NULL)
		{
			free(tmp->heredoc_file);
			tmp->heredoc_file = NULL;
		}
		if (tmp->store != NULL)
		{
			free(tmp->store);
			tmp->store = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_env(t_envarment **my_env)
{
	t_envarment	*tmp;

	while (*my_env)
	{
		tmp = *my_env;
		*my_env = (*my_env)->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
	}
}

void	free_command(t_command *cmd)
{
	if (cmd)
	{
		if (cmd->arg)
		{
			for (int i = 0; cmd->arg[i]; i++)
			{
				free(cmd->arg[i]);
				cmd->arg[i] = NULL;
			}
			free(cmd->arg);
			cmd->arg = NULL;
		}
	}
}

void	ft_free_command(t_command **cmd)
{
	t_command	*tmp_cmd;
	t_command	*next_cmd;

	printf("___free__________\n");
	if (cmd == NULL || *cmd == NULL)
		return ;
	tmp_cmd = *cmd;
	while (tmp_cmd)
	{
		free_args(tmp_cmd->arg);
		if (tmp_cmd->doc)
			ft_free_doc(&tmp_cmd->doc);
		if (tmp_cmd->her)
			ft_free_her(&tmp_cmd->her);
		next_cmd = tmp_cmd->next;
		free(tmp_cmd);
		tmp_cmd = NULL;
		tmp_cmd = next_cmd;
	}
}
