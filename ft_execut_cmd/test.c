
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = dup(STDOUT_FILENO);
    fd = dup(STDIN_FILENO);
    fd = dup(STDIN_FILENO);
    fd = dup(5);
    printf("fd = %d \n", fd);
    if (fd == -1) {
        perror("dup");
        return 1;
    }

    write(fd, "This is a duplicated file descriptor.\n", 38);

    close(fd);
    return 0;
}





























// typedef struct s_command
// {
// 	char				*str_input;
// 	int					len;
// 	enum e_token		type;
// 	enum e_state		state;
// 	struct s_command	*next;
// }						t_command;

// // IT IS IMPORTANT TO REMOVE THE LIBRARIES WE USED
// # include <string.h>

// // call all the libriries we need in the project
// # include "./includes/libft/libft.h"
// # include <curses.h>
// # include <dirent.h>
// # include <errno.h>
// # include <fcntl.h>
// t_command *ft_lstnew(void *content, int len, t_token type, t_state state)
// {
// 	t_command *new_node;

// 	new_node = malloc(sizeof(t_command));
// 	if (!new_node)
// 		return (NULL);
// 	new_node->str_input = content;
// 	new_node->len = len;
// 	new_node->type = type;
// 	new_node->state = state;
// 	new_node->next = NULL;
// 	return (new_node);
// }
// t_command	*ft_lstlast(t_command *lst)
// {

// 	t_command	*last;

// 	last = lst;
// 	if (!lst)
// 		return (NULL);

// 	while (last->next != NULL)
// 		last = last->next;
		
// 	return (last);
// }
// void	ft_add(t_command **lst, t_command *new)
// {
// 	t_command	*last;

// 	if (!lst || !new)
// 		return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		last = ft_lstlast(*lst);
// 		last->next = new;
// 	}
// }

// t_command *elem;
// 			while (list )
// 			{
// 				if(list->type == -1)
// 				{
// 					elem = ft_lstnew(list->str_input, list->len, list->type, list->state);
// 					ft_add(&elem, ft_lstnew(list->str_input, list->len, list->type, list->state));
// 				}
				
// 				list = list->next;
// 			}