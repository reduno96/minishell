/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:17:50 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/24 11:58:03 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handl_sig_exec(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
	}
}

void	hhandle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

int	chech_fork(int pid)
{
	if (pid == -1)
	{
		perror("fork");
		g_exit_status = 1;
		return (1);
	}
	return (0);
}
