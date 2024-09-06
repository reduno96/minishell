/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:05:17 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/04 16:56:10 by rel-mora         ###   ########.fr       */
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

void	ft_free_doc(t_redirect **doc)
{
	t_redirect	*tmp;

	while (*doc != NULL)
	{
		tmp = *doc;
		*doc = (*doc)->next;
		if (tmp->store != NULL)
		{
			// free(tmp->store);
			// tmp->store = NULL;
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
        free(tmp->data);
        free(tmp->var);
        free(tmp);
    }
}
void free_command(t_command *cmd)
{
    if (cmd)
    {
        if (cmd->arg)
        {
            for (int i = 0; cmd->arg[i]; i++)
            {
                free(cmd->arg[i]);
            }
            free(cmd->arg);
        }
        free(cmd);
    }
}
// void	free_command(t_command *cmd)
// {
// 	if (cmd)
// 	{
// 		if (cmd->arg)
// 		{
// 			for (int i = 0; cmd->arg[i]; i++)
// 				free(cmd->arg[i]);
// 			free(cmd->arg);
// 		}
// 		if (cmd->store_her)
// 		{
// 			for (int i = 0; cmd->store_her[i]; i++)
// 				free(cmd->store_her[i]);
// 			free(cmd->store_her);
// 		}
// 		if (cmd->doc)
// 			ft_free_doc(&cmd->doc);
// 		free(cmd);
// 	}
// }

void	ft_free_command(t_command *cmd)
{
	if (cmd)
    {
        if (cmd->arg)
        {
            for (int i = 0; cmd->arg[i]; i++)
            {
                free(cmd->arg[i]);
            }
            free(cmd->arg);
        }
		if (cmd->store_her)
		{
			for (int i = 0; cmd->store_her[i]; i++)
				free(cmd->store_her[i]);
			free(cmd->store_her);
		}
		if (cmd->doc)
			ft_free_doc(&cmd->doc);
		free(cmd);
    }
}
