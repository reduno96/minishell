/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/27 17:58:31 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ff(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	char *str_input;
	t_command *x;

	x = NULL;
	while (1)
	{
		str_input = readline("minishell: ");
		if (!str_input)
			exit(1);
		ft_lexer(str_input, &x);
		if (ft_search(str_input, "exit"))
			exit(0);
		// free(&x);
	}
	atexit(ff);
}