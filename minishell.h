/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:49:25 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/18 18:52:58 by rel-mora         ###   ########.fr       */
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


// ---function to skip---
void		ft_skip_spaces(t_splitor **tmp_x);
void		ft_skip_spaces_in_count(t_splitor **tmp_x);
void		ft_skip_quote(t_splitor **tmp_x, int *i, t_command **new_node);
void ft_skip_not_word(t_splitor **tmp_x, t_envarment *my_env);
void ft_skip_spaces_in_count__2(t_splitor **tmp_x);
// ---function to join---
char		**ft_double_and_sigle(t_splitor **tmp_x, t_envarment *my_env, int j, char ***arr_join);
void		ft_join_double( char ***join, t_splitor **tmp_x,
				t_envarment *my_env, int j);
char		**ft_word(t_splitor **tmp_x, t_envarment *my_env, int j, char ***arr_arg);
void	ft_join_words(char ***join, t_splitor **tmp_x, t_envarment *my_env, int j);
void	ft_join_word_2(char ***join, t_splitor **tmp_x,
		t_envarment *my_env, int j);
// Assuming these are defined somewhere
void		ft_command(t_splitor **x, t_command **cmd, t_envarment *my_env);
void		ft_free_lexer(t_splitor **x);
// void		ft_putstr_fd(const char *s, int fd);
// int			ft_strlen(const char *s);
int			ft_lexer(char *str_input, t_splitor **x);
void		ft_get_word(char *s, t_idx *var, t_splitor **x);
void		ft_get_char(char *s, t_idx *var, t_splitor **x);
t_envarment	*ft_stock_envarment(char **env);
void		print_t_command(t_splitor *cmd);
void		print_redirect_list(t_redirect *head);
// ---------
void		ft_free_env(t_envarment **x);
void		ft_free_lexer(t_splitor **x);
void		ft_free_command(t_command **lst);
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
char		*ft_expand(char *arg, t_envarment **my_env);
// ---------
void		ft_count_parameters(t_splitor *tmp_x, int *count);
void		ft_command(t_splitor **x, t_command **cmd, t_envarment *env);
void		ft_add_command(t_command **lst, t_command *new);
t_command	*ft_new_command(int count, t_splitor **tmp_x, t_envarment *env);
t_command	*ft_last_command(t_command *lst);
char **ft_join_arg(char **arg, char **join);
// ---------
void		ft_not_pipe(t_command **new_node, int *i, t_splitor **tmp_x,
				t_envarment *my_env);

void		ft_skip_spaces(t_splitor **tmp_x);
void		ft_skip_spaces_in_count(t_splitor **tmp_x);

void		ft_skip_general(t_splitor **tmp_x, int *i, t_command **new_node,
				t_envarment *my_env);

// ---------
void		ft_fill_red(t_command **cmd, t_splitor **x, t_envarment *my_env);
void		ft_fill_her(t_command **new_node);
void		ft_check_doc(t_command **new_node);
t_redirect	*ft_new_redir(void *content, t_token type, int is_amb);
void		ft_add_redir(t_redirect **lst, t_redirect *new);
t_redirect	*ft_last_redir(t_redirect *lst);

void	ft_join_arr(char ***arr_join, char *in);
int	ft_len_arg(char **arg);
char	**ft_split_expand(char ***join, char *s,  int bo);

//////////////////////  Execution  ////////////////////////

void			ft_exute(t_envarment **var, t_command *list);
void			ft_free_leaks(t_command *list, t_envarment **var);
void			parent_proc(int pid);
void			hundle_redirections(t_command *list);
void			run_command(t_command *list, t_envarment **var);
int				is_directory(char *path);
void			ft_access_2(char *ptr, char **str);
void			ft_access_1(char *ptr, char **str);
void			ft_access(char 	*ptr ,char  **str );
int 			built_in_exist( t_command *list) ;
void			built_in(t_envarment **var ,t_command *list );
void			execution_cmd(t_command *list, char **new);
int				run_herdoc_built(t_envarment **var, t_command *cmd);




int				ft_strcmp(char *s1, char *s2);
char			**create_argv(t_splitor *elem);
char			*path_command(char *ptr, char **env);
t_envarment		*ft_stock_envarment(char **env);
int				test_exist(t_envarment **var, char **list);
void			run_simple_cmd(t_command *list, t_envarment **var);
void			free_args(char **args);
char			**split_line(char *ptr);
char			**split_var(char *ptr);
void			print_export(t_envarment **var);


void			hundle_command(t_command *list, char **env);
void			handle_pipe(t_command *list, t_envarment **var);


///////////////////////// Redirections  //////////////////////////
void			hundle_redir_out(char *file);
void			hundle_redir_in(char *file);
void			hundle_dredir_out(char *file);

/////////////////////////  her doc  //////////////////////////
int				herdoc_exist(t_command *list);
void			handle_here_doc(t_envarment **var,  t_command *tmp);
t_here_doc		*new_node_her(char *file, int fd, int x, int is_expand);
void			add_back_node_her(t_here_doc **her, t_here_doc *new_her);


/////////////////////////  function redirections  //////////////////////////
char			**get_len(char **args, t_redirect *redir);
char			*git_type_redir(t_redirect *redir);
char			**ft_new_args(char **args, t_redirect *redir);
int				test_redir_here_doc(t_command *list);


/////////////////////////  execut_cmd  //////////////////////////
int				pipe_exist(t_command *list);
int				num_pipe(t_command *list);
char			*command_execut(t_command *list);
int				**return_pipe(int num_cmd);
t_command		*get_list_command(t_command *list);
void			close_free_wait(int *pids, int **pipefd, int num_cmd);
void			child_process(int **pipefd, int i, t_command *tmp_cmd, char **env,
					int num_cmd); //, int *red);

/////////////////////////  signal  //////////////////////////

int				hundle_file_herdoc(t_command *list);

 // ///////            Commands         //////////////////////////////////
void            ft_cd( t_envarment **var,t_command *list , char **env);
void            ft_pwd(t_command *list);
void            ft_export( t_envarment **var , t_command *str );
void            ft_env( t_envarment **var);
void            ft_unset(t_envarment **var , t_command *list);
void            ft_echo(t_command *list );
void			ft_exit(t_envarment **var ,t_command *list);
char 			**array_env(t_envarment **var);
char			*ft_strjoin_1(char *s1, char *s2);
int				len_var(t_envarment *var);
int				count_herdoc(t_command *tmp);


//////////////////////     free      /////////////////////////////////
void		free_ft_split(char 	**list);
int			check_is_valid(char 	*str );
void		ft_error(char 	*str , char *ptr);
char		*ft_getenv(char *path, char **env);
void 	free_pid_pipe(int *pids, int **pipefd, int num_cmd);

#endif
