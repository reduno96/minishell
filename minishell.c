/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/29 16:05:55 by rel-mora         ###   ########.fr       */
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

int	ft_search_env(char *s, char *d)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(d);
	while (s[i] && s[i])
	{
		if (s[i] == d[j])
			j++;
		if (len == j && s[i + 1] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char			*str_input;
	t_command		*x;
	t_environment	*my_env;

	x = NULL;
	my_env = NULL;
	ft_fill_env(&my_env, env);
	while (1)
	{
		str_input = readline("minishell: ");
		if (!str_input)
			exit(1);
		add_history(str_input);
		ft_lexer(str_input, &x);
		ft_check_env(&x, my_env);
		ft_free_env(x);
		x = NULL;
		if (ft_search(str_input, "exit"))
			exit(0);
		free(str_input);
		system("leaks minishell");
	}
}
