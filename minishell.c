/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/28 14:42:58 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ff(void)
{
	system("leaks minishell");
}

void	ft_join_quote(t_splitor **tmp_x, char *s)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->state == D || (*tmp_x)->state == S))
	{
		ft_strjoin(s, (*tmp_x)->in);
		(*tmp_x) = (*tmp_x)->next;
	}
	free(s);
}

void	print_envarment(t_envarment *env)
{
	t_envarment	*current;

	current = env;
	while (current != NULL)
	{
		printf("%s=%s\n", (char *)current->var, (char *)current->data);
		current = current->next;
	}
}
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
int	ft_ambiguous(t_splitor *x, t_command *cmd, t_envarment *my_env)
{
	t_splitor	*tmp_x;

	(void)cmd;
	(void)my_env;
	tmp_x = x;
	while (tmp_x != NULL)
	{
		if (tmp_x->type == '<' || tmp_x->type == '>'
			|| tmp_x->type == DREDIR_OUT)
		{
			if (tmp_x->is_amb == 1)
				return (1);
		}
		tmp_x = tmp_x->next;
	}
	return (0);
}
void	ft_initialize(t_splitor *x, t_command *cmd, t_envarment *my_env,
		char **env)
{
	(void) env;
	// ft_check_env(&x, my_env);
	// if (ft_ambiguous(x, cmd, my_env))
	// {
	// 	ft_putstr_fd("Syntax Error:\n", 2);
	// 	return ;
	// }
	ft_command(&x, &cmd, my_env);
	ft_exute(my_env, cmd, env);
	ft_free_lexer(&x);
}
void	ft_reader(t_splitor *x, t_command *cmd, t_envarment *my_env, char **env)
{
	char	*str_input;

	while (1)
	{
		str_input = readline("\033[36m➨ minishell $:\033[0m  ");
		if (!str_input)
		{
			printf("exit\n");
			//
			exit(0);
		}
		if (ft_strlen(str_input) > 0)
			add_history(str_input);
		if (ft_lexer(str_input, &x))
		{
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
void	ft_d(int signal)
{
	printf("fdf\n");
	if (signal == SIGQUIT)
		printf("quit\n");
}
int	main(int ac, char **av, char **env)
{
	t_splitor	*x;
	t_envarment	*my_env;
	t_command	*cmd;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, handle_sig);
	(void)ac;
	(void)av;
	my_env = NULL;
	my_env = ft_stock_envarment(env);
	using_history();
	x = NULL;
	cmd = NULL;
	ft_reader(x, cmd, my_env, env);
	ft_free_env(&my_env);
}
