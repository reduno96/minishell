/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/07 08:00:45 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

// call all the libriries we need in the project
# include "./includes/libft/libft.h"
# include "structures.h"
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
int				ft_search(char *s, char *d);
int				ft_isspace(char c);
void			print_str_input(void *str_input);
void			print_t_command(t_splitor *cmd);
t_token			ft_get_token(char str_input);
int				ft_check_input(char str_input);
t_state			ft_get_state(t_idx *var, char str_input);
int				ft_handler_syn_error(t_splitor **x);
void			ft_lexer(char *input, t_splitor **x);

void			ft_fill_env(t_environment **my_env, char **env);
int				ft_search_env(char *s, char *d);
void			ft_check_env(t_splitor **x, t_environment *my_env);
void			ft_add_node(t_environment **lst, t_environment *new);
t_environment	*ft_new_node(void *content);
t_environment	*ft_last_node(t_environment *lst);
void			check_syn(t_splitor **x);
void			ft_free_env(t_splitor *x);
void			ft_free_command(t_command *lst);
void			ft_add_command(t_command **lst, t_command *new);

void			ft_skeep_space(t_splitor **tmp_x);

int				ft_check_command(t_splitor *tmp_x);

t_command		*ft_new_command(int count, t_splitor **tmp_x);
t_command		*ft_last_command(t_command *lst);
void			ft_command(t_splitor **x, t_environment **my_env,
					t_command **cmd);
void			print_env(t_environment **my_env);
void			ft_check_doc(t_command **new_node);

#endif
