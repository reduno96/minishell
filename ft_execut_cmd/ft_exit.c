/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:14 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/02 18:58:52 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_len_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		i++;
	return (i);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_when_exit(t_envarment *var, char *str, int fd, t_command *cmd)
{
	ft_putstr_fd(str, fd);
	ft_free_command(cmd);
	ft_free_env(&var);
}
void	ft_exit(t_envarment *var, t_command *cmd)
{
	int	len;

	len = ft_len_arg(cmd->arg);
	if (len == 1)
	{
		ft_free_when_exit(var, "exit\n", 1, cmd);
		{
g_exit_status = 0;
		exit(0);
		}
	}
	else if (len == 2 && is_number(cmd->arg[1]))
	{
		ft_free_when_exit(var, "exit\n", 1, cmd);
		g_exit_status = ft_atoi(cmd->arg[1]);
		exit(ft_atoi(cmd->arg[1]));
	}
	else if (len > 2 && is_number(cmd->arg[1]))
		ft_putstr_fd(" exit: too many arguments\n", 2);
	else
	{
		g_exit_status = 2;
		ft_free_when_exit(var, "exit: numeric argument required\n", 2, cmd);
		exit(2);
	}
}
