SRC= minishell.c \
	lexer_utils.c \
	lexer.c \
	ft_handle_synx.c \
	ft_nodes_env.c \
	ft_free.c \
	ft_parsser.c\
	ft_parsser_utils_2.c \
	ft_parsser_utils.c \
	ft_direction.c \
	ft_direction_utils.c \
	ft_execut_cmd/execute.c ft_execut_cmd/functions.c ft_execut_cmd/ft_cd.c   ft_execut_cmd/ft_pwd.c  ft_execut_cmd/ft_exit.c \
	#ft_execut_cmd/ft_export.c ft_execut_cmd/utilis_env.c  ft_execut_cmd/ft_unset.c ft_execut_cmd/ft_env.c \

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline -lncurses

CC = cc


NAME = minishell

LIBFT = ./includes/libft/libft.a
FLDLIBFT= ./includes/libft

#include readLine in MacOS
INRL = -lreadline -L/goinfre/bouhammo/homebrew/opt/readline/lib
LNRL= -lreadline -L/goinfre/bouhammo/homebrew/opt/readline/include

# include readLine in Linux
# INRL = -lreadline -L/usr/include/readline
# LNRL= -lreadline -L/usr/include/readline



all : ${LIBFT} ${NAME}

%.o: %.c minishell.h structures.h
	${CC} ${CFLAGS} -c  $< -o $@

${NAME} : minishell.h structures.h ${OBJ}
		${CC} ${FLAGS}   ${SRC} ${LIBFT} ${INRL} ${LNRL} -o ${NAME}

${LIBFT}:
	make -C ${FLDLIBFT}
	make bonus -C ${FLDLIBFT}

clean:
	make fclean -C ./includes/libft
	@rm -rf ${OBJ}
	@echo "\033[34mminishell is clean from object files\033[0m"

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[34mminishell is clean from program file\033[0m"

re : fclean all

.PHONY: all clean fclean re
