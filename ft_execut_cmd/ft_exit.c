/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 23:39:14 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/19 15:24:50 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../minishell.h"

int	ft_len_arg(char **arg)
{
	int	i;
	if(arg == NULL || arg[0] == NULL)	
		return 0;
	i = 0;
	while (arg[i] != NULL)	
	{
		i++;	
	}
	return (i);
}

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
	{
		i++;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				return (0);
			i++;
		}
	}
	else
	{
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

void	ft_free_when_exit(t_envarment **var, char *str, int fd, t_command *cmd)
{
	(void)cmd;
	(void)var;
	(void)str;
	(void)cmd;
	ft_putstr_fd(str, fd);
	ft_free_command(&cmd);
	ft_free_env(var);
}

void	ft_exit_comp(int len, char *ptr)
{
	if (len == 2 && is_number(ptr) && ptr[0] == '-')
	{
		g_exit_status = 156;
		ft_putstr_fd("exit\n", 1);
		exit(156);
	}
	else if (len == 2 && !is_number(ptr))
	{
		g_exit_status = 156;
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(" numeric argument required\n", 2);
		exit(255);
	}
	else if (len > 2)
	{
		g_exit_status = 1;
		ft_putstr_fd(" too many arguments\n", 2);
	}
}

void	ft_exit(t_envarment **var, t_command *cmd)
{
	int	len;

	len = ft_len_arg(cmd->arg);
	if (len == 1)
	{
		g_exit_status = 0;
		ft_free_when_exit(var, "exit\n", 1, cmd);
		exit(0);
	}
	else if (len == 2 && is_number(cmd->arg[1]) && (cmd->arg[1][0] != '+'
		|| cmd->arg[1][0] != '+'))
	{
		g_exit_status = ft_atoi(cmd->arg[1]);
		exit(ft_atoi(cmd->arg[1]));
	}
	else if (len == 2 && is_number(cmd->arg[1]) && cmd->arg[1][0] == '+')
	{
		g_exit_status = ft_atoi(cmd->arg[1]);
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(cmd->arg[1]));
	}
	else
		ft_exit_comp(len, cmd->arg[1]);
}


