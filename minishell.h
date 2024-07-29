/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/07/29 16:25:59 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

typedef struct s_idx
{
	int						i;
	int						j;
	int						len;
	int						start;
	int						state;
	int						in_s_quote;
	int						in_d_quote;
}							t_idx;

typedef enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}							t_token;

typedef enum e_state
{
	IN_DQUOTE,
	IN_SQUOTE,
	GENERAL,
	NUL,
}							t_state;
typedef struct s_command
{
	char					*str_input;
	int						len;
	enum e_token			type;
	enum e_state			state;
	struct s_command		*next;
}							t_command;

typedef struct s_environment
{
	char					*line;
	struct s_environment	*next;
}							t_environment;


// call all the libriries we need in the project
# include "./includes/libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// function we use
int							ft_search(char *s, char *d);
int							ft_isspace(char c);
void						print_str_input(void *str_input);
void						print_t_command(t_command *cmd);
t_token						ft_get_token(char str_input);
int							ft_check_input(char str_input);
t_state						ft_get_state(t_idx *var, char str_input);
int							ft_handler_syn_error(t_command **x);
void						ft_lexer(char *input, t_command **x);

void						ft_fill_env(t_environment **my_env, char **env);
int							ft_search_env(char *s, char *d);
void						ft_check_env(t_command **x, t_environment *my_env);
void						ft_add_node(t_environment **lst,
								t_environment *new);
t_environment				*ft_new_node(void *content);
t_environment				*ft_last_node(t_environment *lst);
void						check_syn(t_command **x);
void	ft_free_env(t_command *x);

#endif