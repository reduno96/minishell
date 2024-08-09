/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/09 13:20:52 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ff(void)
{
	system("leaks minishell");
}

// void	print_env(t_envarment **my_env)
// {
// 	t_envarment	*current_node;

// 	current_node = *my_env;
// 	while (current_node != NULL)
// 	{
// 		printf("%s\n", current_node->line);
// 		current_node = current_node->next;
// 	}
// }

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

// ------------------------------
int	main(int ac, char **av, char **env)
{
	char		*str_input;
	t_splitor	*x;
	t_envarment	*my_env;
	t_command	*cmd;

	(void)ac;
	(void)av;
	x = NULL;
	my_env = NULL;
	my_env = ft_stock_envarment(env);
	// print_envarment(my_env);
	using_history();
	(void)cmd;
	while (1)
	{
		cmd = NULL;
		str_input = readline("\033[36m➨ minishell $:\033[0m  ");
		if (!str_input)
			exit(1);
		if (ft_strlen(str_input) > 0)
			add_history(str_input);
		ft_lexer(str_input, &x);
		ft_check_env(&x, my_env);
		ft_command(&x, &my_env, &cmd);
		ft_exute(my_env, cmd, x);
		ft_free_lexer(&x);
		ft_free_command(cmd);
		x = NULL;
		if (ft_search(str_input, "exit"))
			exit(0);
		free(str_input);
	}
	ft_free_env(&my_env);
}
