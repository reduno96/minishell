/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:08:06 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/25 14:54:37 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ff()
{
	system("leaks minishell");
}
int	main(int ac, char **av, char **env)
{
	char *str_input;
	t_command *lexer_command;



	str_input = readline("minishell: " );
	// printf(":%s\n", str_input);/÷
		while(1)
		;
	while(1)
	{
		if (ft_search(lexer_command->str_input, "exit"))
			exit(0);
	}
	atexit(ff);
}