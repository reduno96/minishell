NAME	=		pipex

SRCS	=		pipe.c

FLAGS	=		-Wall -Werror -Wextra

LIBFT	=		/Users/bouhammo/Desktop/minishell_5/includes/libft/libft.a


all: $(NAME)

$(NAME): $(LIBFT) $(SRCS) $(HEADER)
	$(CC) $(LIBFT) $(SRCS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

clean:
	make fclean -C libft

fclean: clean
	rm -f $(NAME)
#rm -f $(LIBFT)

re : fclean all

