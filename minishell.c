/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/31 14:27:55 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ff(void)
{
	system("leaks minishell");
}

void	print_env(t_environment **my_env)
{
	t_environment	*current_node;

	current_node = *my_env;
	while (current_node != NULL)
	{
		printf("%s\n", current_node->line);
		current_node = current_node->next;
	}
}
void	ft_join_quote(t_splitor **tmp_x, char *s)
{
	while ((*tmp_x) != NULL && ((*tmp_x)->state == IN_DQUOTE
			|| (*tmp_x)->state == IN_SQUOTE))
	{
		ft_strjoin(s, (*tmp_x)->str_input);
		(*tmp_x) = (*tmp_x)->next;
	}
	free(s);
}
void	ft_command(t_splitor **x, t_environment **my_env, t_command **cmd)
{
	t_splitor	*tmp_x;
	t_info		arg;
	int			cout_pipe;

	cout_pipe = 0;
	(void)my_env;
	arg.s = NULL;
	arg.i = NULL;
	arg.o = NULL;
	arg.h = NULL;
	arg.d = NULL;
	tmp_x = *x;
	while (tmp_x != NULL)
	{
		while (tmp_x != NULL && tmp_x->type != '|')
		{
			while (tmp_x != NULL && tmp_x->type == ' '
				&& tmp_x->state == GENERAL)
				tmp_x = tmp_x->next;
			if (tmp_x->type == -1 || tmp_x->type == '$')
				arg.s = ft_strdup(tmp_x->str_input);
			else if (tmp_x->type == '<')
				arg.i = ft_strdup(tmp_x->str_input);
			else if (tmp_x->type == '>')
				arg.o = ft_strdup(tmp_x->str_input);
			else if (tmp_x->type == HERE_DOC)
				arg.h = ft_strdup(tmp_x->str_input);
			else if (tmp_x->type == DREDIR_OUT)
				arg.d = ft_strdup(tmp_x->str_input);
			ft_add_commad(cmd, ft_new_command(&arg));
			tmp_x = tmp_x->next;
		}
		cout_pipe++;
		if (tmp_x != NULL)
			tmp_x = tmp_x->next;
	}
}

int	main(int ac, char **av, char **env)
{
	char			*str_input;
	t_splitor		*x;
	t_environment	*my_env;
	t_command		*cmd;

	(void)ac;
	(void)av;
	x = NULL;
	my_env = NULL;
	cmd = NULL;
	ft_fill_env(&my_env, env);
	(void)cmd;
	while (1)
	{
		str_input = readline("minishell: ");
		if (!str_input)
			exit(1);
		add_history(str_input);
		ft_lexer(str_input, &x);
		ft_check_env(&x, my_env);
		ft_command(&x, &my_env, &cmd);
		ft_free_env(x);
		x = NULL;
		if (ft_search(str_input, "exit"))
			exit(0);
		free(str_input);
	}
}
