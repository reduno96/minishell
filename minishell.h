/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <reduno96@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/29 23:11:02 by rel-mora         ###   ########.fr       */
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
# include <stdbool.h>
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

//////////////////////////////  Parsser  /////////////////////////////////
// ---------
// Assuming these are defined somewhere
void		ft_command(t_splitor **x, t_command **cmd, t_envarment *my_env);
void		ft_free_lexer(t_splitor **x);
void		ft_free_command(t_command *cmd);
// void		ft_putstr_fd(const char *s, int fd);
// int			ft_strlen(const char *s);
int			ft_lexer(char *str_input, t_splitor **x);

t_envarment	*ft_stock_envarment(char **env);
void		print_t_command(t_splitor *cmd);
void		print_redirect_list(t_redirect *head);
// ---------
void		ft_free_env(t_envarment **x);
void		ft_free_lexer(t_splitor **x);
void		ft_free_command(t_command *lst);
void		ft_free_split(char **list);
// ---------
int			ft_search(char *s, char *d);
int			ft_isspace(char c);
t_token		ft_get_token(char str_input);
int			ft_check_input(char str_input);
t_state		ft_get_state(t_idx *var, char str_input);
int			ft_condition(t_splitor *start);
int			ft_handler_syn_error(t_splitor **x);
// int			ft_lexer(char *input, t_splitor **x);
// ---------
t_envarment	*new_node(void *var, void *data);
void		add_back_node(t_envarment **lst, t_envarment *new);
t_envarment	*ft_stock_envarment(char **env);
char		*ft_expand(char *arg, t_envarment *my_env);
void		ft_check_env(t_splitor **x, t_envarment *my_env, char **arg, int g);
// ---------
void		ft_command(t_splitor **x, t_command **cmd, t_envarment *env);
void		ft_add_command(t_command **lst, t_command *new);
t_command	*ft_new_command(int count, t_splitor **tmp_x, t_envarment *env);
t_command	*ft_last_command(t_command *lst);
// ---------
void		ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x,
				t_envarment *my_env);
int			ft_check_command(t_splitor *tmp_x);
void		ft_skip_spaces(t_splitor **tmp_x);
void		ft_double_and_sigle(t_splitor **tmp_x, int *i,
				t_command **new_node);
// ---------
void		ft_fill_red(t_command **cmd, t_splitor **x);
void		ft_fill_her(t_command **new_node);
void		ft_check_doc(t_command **new_node);
t_redirect	*ft_new_redir(void *content, t_token type);
void		ft_add_redir(t_redirect **lst, t_redirect *new);
t_redirect	*ft_last_redir(t_redirect *lst);

//////////////////////  Execution  ////////////////////////

void		ft_exute(t_envarment *var, t_command *list, char **env);
int			ft_strcmp(char *s1, char *s2);
char		**create_argv(t_splitor *elem);
char		*path_command(char *ptr);
t_envarment	*ft_stock_envarment(char **env);
int			test_exist(t_envarment *var, char **list);

void	free_args(char **args);  // ft_export
char	**split_line(char *ptr); // ft_export
char	**split_var(char *ptr);  // ft_env
void		print_export(t_envarment *var, t_command *str);
void		execution_cmd(t_command *list, char **new, char **env);
void		hundle_command(t_command *list, char **env);
int			hundle_redirections(t_command *list);
void		handle_pipe(t_command *list, char **env);
// void			handle_here_doc(t_command *tmp);

///////////////////////// Redirections  //////////////////////////
void		hundle_redir_out(char *file);
void		hundle_redir_in(char *file);
void		hundle_dredir_out(char *file);

/////////////////////////  her doc  //////////////////////////
int			herdoc_exist(t_command *list);
void		handle_here_doc(t_command *tmp, char **env);
t_here_doc	*new_node_her(int idx, int i, char *file, int fd, bool expand);
void		add_back_node_her(t_here_doc **her, t_here_doc *new_her);

/////////////////////////  function redirections  //////////////////////////
char		**get_len(char **args, t_redirect *redir);
char		*git_type_redir(t_redirect *redir);
char		**ft_new_args(char **args, t_redirect *redir);
int			test_redir_here_doc(t_command *list);

/////////////////////////  execut_cmd  //////////////////////////
int			pipe_exist(t_command *list);
int			num_pipe(t_command *list);
char		*command_execut(t_command *list);
int			**return_pipe(int num_cmd);
t_command	*get_list_command(t_command *list);
void		close_free_wait(int *pids, int **pipefd, int num_cmd,
				t_command *tmp_cmd);
void	child_process(int **pipefd, int i, t_command *tmp_cmd, char **env,
					int num_cmd); //, int *red);
void		handle_pipe(t_command *list, char **env);

/////////////////////////  signal  //////////////////////////

// ///////            Commands         //////////////////////////////////
// int			builtin_cmd(t_envarment *var ,t_command *list ,char  **env);
int			ft_cd(t_command *list);
int			ft_pwd(t_command *va_list);
int			ft_export(t_envarment *var, t_command *str);
int			ft_env(t_envarment *var);
int			ft_unset(t_envarment *var, t_command *list);
int			ft_echo(t_command *list, char **env);
void		ft_echo_flag(t_command *list);
int			ft_exit(t_envarment *var, t_command *list);

#endif
