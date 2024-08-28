/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mora <rel-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 07:58:38 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/26 12:33:25 by rel-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <stdbool.h>
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
	enum e_state		state;
	struct s_splitor	*next;
	struct s_splitor *prev;
}						t_splitor;

typedef struct s_envarment
{
	char				*var;
	char				*data;
	struct s_envarment	*next;
}						t_envarment;

typedef struct s_command
{
	char				*content;
	char				**arg;
	t_redirect			*doc;
	char				**store_her;
	int					is_pipe;
	int					len;
	struct s_command	*next;
}						t_command;

typedef struct s_here_doc
{
	int					indx_cmd;
	int					indx;
	char				*store;
	int					fd;
	bool				is_expanded;
	struct s_here_doc	*next;
}						t_here_doc;

#endif