/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/12 22:15:29 by rel-mora         ###   ########.fr       */
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

// ---------
void		print_t_command(t_splitor *cmd);
void		print_redirect_list(t_redirect *head);
// ---------
int			ft_search(char *s, char *d);
int			ft_isspace(char c);
t_token		ft_get_token(char str_input);
int			ft_check_input(char str_input);
t_state		ft_get_state(t_idx *var, char str_input);
int			ft_condition(t_splitor *start);
int			ft_handler_syn_error(t_splitor **x);
void		ft_lexer(char *input, t_splitor **x);

t_envarment	*new_node(void *var, void *data);
void		add_back_node(t_envarment **lst, t_envarment *new);
t_envarment	*ft_stock_envarment(char **env);
void		ft_check_env(t_splitor **x, t_envarment *my_env);

void		ft_free_env(t_envarment **x);
void		ft_free_lexer(t_splitor **x);
void		ft_free_command(t_command *lst);

void		check_syn(t_splitor **x);
void		ft_add_command(t_command **lst, t_command *new);

void		ft_skip_spaces(t_splitor **tmp_x);

int			ft_check_command(t_splitor *tmp_x);

void		ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x);

t_command	*ft_new_command(int count, t_splitor **tmp_x);
t_command	*ft_last_command(t_command *lst);
void		ft_command(t_splitor **x, t_command **cmd);

// ---------
void		ft_check_doc(t_command **new_node);
t_redirect	*ft_new_redir(void *content, t_token type);
void		ft_add_redir(t_redirect **lst, t_redirect *new);
t_redirect	*ft_last_redir(t_redirect *lst);

//////////////////////  Execution  ////////////////////////

void		ft_exute(t_envarment *var, t_command *list, t_splitor *x);
int			ft_strcmp(char *s1, char *s2);
char		**create_argv(t_splitor *elem);
char		*path_command(char *ptr);
// t_envarment *ft_stock_envarment(char **env);
// int 	test_exist(t_envarment *var , char **list);
// void   affiche_free_env(t_envarment *var , t_command *save);

// //    export
// t_envarment  *new_node(void *var, void *data);
// void    		add_back_node(t_envarment **lst, t_envarment *new);

// ///////            Commands         ///////
void		ft_cd(t_command *list);
void		ft_pwd(t_command *va_list);
// void 		ft_export( t_envarment *var , t_command *str);
// void 		ft_unset(t_envarment *var , t_command *list);
// void 		ft_env( t_envarment *var ,t_command *str );

#endif
