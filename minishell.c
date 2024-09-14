/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/14 17:36:22 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ff(void)
// {
// 	system("leaks minishell");
// }

// void	print_envarment(t_envarment *env)
// {
// 	t_envarment	*current;

// 	current = env;
// 	while (current != NULL)
// 	{
// 		// printf("%s=%s\n", (char *)current->var, (char *)current->data);
// 		current = current->next;
// 	}
// }
void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_initialize(t_splitor *x, t_command *cmd, t_envarment **my_env,
		char **env)
{
	if (x != NULL && my_env != NULL)
	{
		ft_command(&x, &cmd, *my_env);
		ft_exute(my_env, cmd);
		ft_free_command(cmd);
	}
	(void)env;
	(void)my_env;
	(void)cmd;
	ft_free_lexer(&x);
}

void	ft_free_when_exit_1(t_splitor *x, t_command *cmd, t_envarment **my_env)
{
	printf("exit\n");
	ft_free_command(cmd);
	ft_free_lexer(&x);
	ft_free_env(my_env);
	g_exit_status = 0;
	exit(0);
}

void	ft_reader(t_splitor *x, t_command *cmd, t_envarment **my_env, char **env)
{
	char	*str_input;

	while (1)
	{
		str_input = readline("\033[36m➨ minishell $:\033[0m  ");
		if (!str_input)
			ft_free_when_exit_1(x, cmd, my_env);
		if (ft_strlen(str_input) > 0)
			add_history(str_input);
		if (ft_lexer(str_input, &x))
		{
			g_exit_status = 258;
			ft_putstr_fd("Syntax Error:\n", 2);
			ft_free_lexer(&x);
		}
		else
			ft_initialize(x, cmd, my_env, env);
		ft_free_command(cmd);
		cmd = NULL;
		x = NULL;
		free(str_input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_splitor	*x;
	t_envarment	*my_env;
	t_command	*cmd;

	// atexit(ff);
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	(void)ac;
	(void)av;
	my_env = NULL;
	my_env = ft_stock_envarment(env);
	using_history();
	x = NULL;
	cmd = NULL;
	ft_reader(x, cmd, &my_env, env);
	ft_free_env(&my_env);
	return (0);
}
