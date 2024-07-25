SRC= minishell.c \
	utils.c \

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror
RFLAGS = -lreadline -lncurses

CC = cc


NAME = minishell

LIBFT = ./includes/libft/libft.a
FLDLIBFT= ./includes/libft

#include readLine
INRL = -lreadline -L/goinfre/rel-mora/homebrew/opt/readline/lib
LNRL= -lreadline -L/goinfre/rel-mora/homebrew/opt/readline/include



all : ${LIBFT} ${NAME}

%.o: %.c minishell.h
	${CC} ${CFLAGS} -c  $< -o $@

${NAME} : minishell.h
		${CC} ${FLAGS} ${LIBFT} ${INRL} ${LNRL} ${SRC} -o ${NAME}

${LIBFT}:
	make -C ${FLDLIBFT}

clean:
	make fclean -C ./includes/libft
	@rm -rf ${OBJ} ${NAME}
	@echo "\033[34mminishell is clean from object files\033[0m"

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[34mminishell is clean from program file\033[0m"

re : fclean all

.PHONY: all clean fclean re
