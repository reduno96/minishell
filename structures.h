/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:58:38 by rel-mora          #+#    #+#             */
/*   Updated: 2024/09/15 14:05:12 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdbool.h>

int						g_exit_status;


typedef struct s_idx
{
	int					i;
	int					j;
	int					len;
	int					start;
	int					state;
	int					in_s;
	int					in_d;
}						t_idx;


typedef enum e_token
{
	nothing = 0,
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
}						t_token;

typedef struct s_redirect
{
	t_token				type;
	int					is_amb;
	char				*store;
	struct s_redirect	*next;
}						t_redirect;

typedef enum e_state
{
	D,
	S,
	G,
	NUL,
}						t_state;
typedef struct s_splitor
{
	char				*in;
	int					len;
	enum e_token		type;
	int					is_amb;
	int					is_exp;
	enum e_state		state;
	struct s_splitor	*next;
	struct s_splitor	*prev;
}						t_splitor;

typedef struct s_envarment
{
	char				*var;
	char				*data;
	struct s_envarment	*next;
}						t_envarment;

typedef struct s_here_doc
{
	char				*store;
	int					fd;
	char				*heredoc_file;
	int					idx;
	int					expad;
	struct s_here_doc	*next;
}						t_here_doc;

typedef struct s_command
{
	char				*content;
	char				**arg;
	t_redirect			*doc;
	t_here_doc			*her;
	char				**store_her;
	char				**ar_env;
	int					is_amb;
	int					is_exp;
	int					is_pipe;
	int					len;
	struct s_command	*next;
}						t_command;



typedef struct s_pre
{
	char				*final;
	int					i;
	int					j;
	int					is_expand;
		t_command	*tmp_cmd;
	t_splitor	*tmp_x;
}						t_pre;

typedef struct pipe
{
	int			num_cmd;
	int			**pipefd;
	t_command	*tmp_cmd;
	int		*pids;
	int			heredoc_fd;
	int			i;
	char		*ptr;
}		t_pipe;
#endif