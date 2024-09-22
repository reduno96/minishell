/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:05:17 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/21 15:42:45 by rel-mora         ###   ########.fr       */
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

void	ft_free_env(t_envarment **my_env)
{
    t_envarment	*tmp;

    while (*my_env) {
        tmp = *my_env;
        *my_env = (*my_env)->next;
		// printf("............       %s\n", tmp->var);
        free(tmp->data);
        free(tmp->var);
        free(tmp);
    }
}

void free_command(t_command *cmd)
{
    if (cmd)
    {
		printf("i'm here \n");
        if (cmd->arg)
        {
			free(cmd->content);
            for (int i = 0; cmd->arg[i]; i++)
            {
                free(cmd->arg[i]);
            }
            free(cmd->arg);
        }
        free(cmd);
    }
}

void	ft_free_command(t_command **cmd)
{
	t_command *tmp_cmd;

	printf("i'm here in ft_free_cmd\n");
	tmp_cmd = *cmd;
	while(tmp_cmd)
    {
        free_command(tmp_cmd);
		if (tmp_cmd->doc)
			ft_free_doc(&tmp_cmd->doc);
		free(tmp_cmd);
		tmp_cmd = NULL;
		if (tmp_cmd != NULL)
			tmp_cmd =tmp_cmd->next;
    }
}

