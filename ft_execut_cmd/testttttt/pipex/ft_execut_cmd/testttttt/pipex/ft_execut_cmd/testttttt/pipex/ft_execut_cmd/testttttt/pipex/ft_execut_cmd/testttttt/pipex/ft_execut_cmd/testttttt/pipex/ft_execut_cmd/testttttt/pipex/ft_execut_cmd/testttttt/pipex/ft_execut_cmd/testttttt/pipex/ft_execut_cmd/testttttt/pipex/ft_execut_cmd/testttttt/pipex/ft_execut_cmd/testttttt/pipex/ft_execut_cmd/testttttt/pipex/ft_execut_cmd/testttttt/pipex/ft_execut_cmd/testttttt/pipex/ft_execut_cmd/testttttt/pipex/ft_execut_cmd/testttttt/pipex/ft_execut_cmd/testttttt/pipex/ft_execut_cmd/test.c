// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/09 19:20:12 by bouhammo          #+#    #+#             */
// /*   Updated: 2024/08/13 11:01:31 by bouhammo         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */






#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to create a pipe and handle errors
void create_pipe(int pipefd[2]) {
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

// Function to execute a command
void execute_command(const char *command, char *const argv[], int input_fd, int output_fd) {
    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
    execve(command, argv, NULL);
    perror("execve");
    exit(EXIT_FAILURE);
}

// Function to fork a process and execute a command in the child process
pid_t fork_and_execute(const char *command, char *const argv[], int input_fd, int output_fd) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        execute_command(command, argv, input_fd, output_fd);
    }
    return pid;
}

// Main function to execute the pipeline: cat file | grep "a" | wc -l
int main() {
    int pipefd1[2], pipefd2[2];
    pid_t pid1, pid2, pid3;

    // Create the first pipe (cat -> grep)
    create_pipe(pipefd1);

    // Fork and execute `cat file`
    char *cat_argv[] = {"/bin/cat", "file", NULL};
    pid1 = fork_and_execute("/bin/cat", cat_argv, STDIN_FILENO, pipefd1[1]);

    // Create the second pipe (grep -> wc)
    create_pipe(pipefd2);

    // Fork and execute `grep "a"`
    char *grep_argv[] = {"/bin/grep", "a", NULL};
    pid2 = fork_and_execute("/bin/grep", grep_argv, pipefd1[0], pipefd2[1]);

    // Close the first pipe ends (no longer needed)
    close(pipefd1[0]);
    close(pipefd1[1]);

    // Fork and execute `wc -l`
    char *wc_argv[] = {"/usr/bin/wc", "-l", NULL};
    pid3 = fork_and_execute("/usr/bin/wc", wc_argv, pipefd2[0], STDOUT_FILENO);

    // Close the second pipe ends (no longer needed)
    close(pipefd2[0]);
    close(pipefd2[1]);

    // Wait for all child processes to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}


// #include <unistd.h>
// #include <stdio.h>












// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main() {
//     int pipefd[2];
//     pid_t pid1, pid2;

//     // Create the pipe
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // Fork the first child process for `ls`
//     pid1 = fork();
//     if (pid1 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid1 == 0) {
//         // In the first child process

//         // Close the read end of the pipe
//         close(pipefd[0]);

//         // Redirect stdout to the write end of the pipe
//         dup2(pipefd[1], STDOUT_FILENO);

//         // Close the write end of the pipe (after duplication)
//         close(pipefd[1]);

//         // Execute `ls`
//         char *argv[] = {"/bin/ls", NULL};
//         execve(argv[0], argv, NULL);

//         // If execve fails
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }

//     // Fork the second child process for `wc`
//     pid2 = fork();
//     if (pid2 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid2 == 0) {
//         // In the second child process

//         // Close the write end of the pipe
//         close(pipefd[1]);

//         // Redirect stdin to the read end of the pipe
//         dup2(pipefd[0], STDIN_FILENO);

//         // Close the read end of the pipe (after duplication)
//         close(pipefd[0]);

//         // Execute `wc`
//         char *argv[] = {"/usr/bin/wc", NULL};
//         execve(argv[0], argv, NULL);

//         // If execve fails
//         perror("execve");
//         exit(EXIT_FAILURE);
//     }

//     // Parent process

//     // Close both ends of the pipe
//     close(pipefd[0]);
//     close(pipefd[1]);

//     // Wait for both child processes to finish
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);

//     return 0;
// }















// // int main() {
// //     int fd = dup(STDOUT_FILENO);
// //     fd = dup(STDIN_FILENO);
// //     fd = dup(STDIN_FILENO);
// //     fd = dup(5);
// //     printf("fd = %d \n", fd);
// //     if (fd == -1) {
// //         perror("dup");
// //         return 1;
// //     }

// //     write(fd, "This is a duplicated file descriptor.\n", 38);

// //     close(fd);
// //     return 0;
// // }





























// // typedef struct s_command
// // {
// // 	char				*str_input;
// // 	int					len;
// // 	enum e_token		type;
// // 	enum e_state		state;
// // 	struct s_command	*next;
// // }						t_command;

// // // IT IS IMPORTANT TO REMOVE THE LIBRARIES WE USED
// // # include <string.h>

// // // call all the libriries we need in the project
// // # include "./includes/libft/libft.h"
// // # include <curses.h>
// // # include <dirent.h>
// // # include <errno.h>
// // # include <fcntl.h>
// // t_command *ft_lstnew(void *content, int len, t_token type, t_state state)
// // {
// // 	t_command *new_node;

// // 	new_node = malloc(sizeof(t_command));
// // 	if (!new_node)
// // 		return (NULL);
// // 	new_node->str_input = content;
// // 	new_node->len = len;
// // 	new_node->type = type;
// // 	new_node->state = state;
// // 	new_node->next = NULL;
// // 	return (new_node);
// // }
// // t_command	*ft_lstlast(t_command *lst)
// // {

// // 	t_command	*last;

// // 	last = lst;
// // 	if (!lst)
// // 		return (NULL);

// // 	while (last->next != NULL)
// // 		last = last->next;
		
// // 	return (last);
// // }
// // void	ft_add(t_command **lst, t_command *new)
// // {
// // 	t_command	*last;

// // 	if (!lst || !new)
// // 		return ;
// // 	if (*lst == NULL)
// // 		*lst = new;
// // 	else
// // 	{
// // 		last = ft_lstlast(*lst);
// // 		last->next = new;
// // 	}
// // }

// // t_command *elem;
// // 			while (list )
// // 			{
// // 				if(list->type == -1)
// // 				{
// // 					elem = ft_lstnew(list->str_input, list->len, list->type, list->state);
// // 					ft_add(&elem, ft_lstnew(list->str_input, list->len, list->type, list->state));
// // 				}
				
// // 				list = list->next;
// // 			}







// #include "minishell.h"

// /*
// ** Runs the binary file by creating a new process and handles signals in case
// ** of interruptions then returns whether it executed successfully or not
// **
// ** @param		path	The path to the binary file
// ** @param		args	The arguments to pass to the system command
// ** @return		-1 on failure, 1 on success
// */

// static int		run_cmd(char *path, char **args)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	signal(SIGINT, proc_signal_handler);
// 	if (pid == 0)
// 		execve(path, args, g_envv);
// 	else if (pid < 0)
// 	{
// 		free(path);
// 		ft_putendl("Fork failed to create a new process.");
// 		return (-1);
// 	}
// 	wait(&pid);
// 	if (path)
// 		free(path);
// 	return (1);
// }

// /*
// ** Checks if the first word in the input is one of the builtin commands, if it
// ** is, it executes it and returns -1, 0, or 1
// **
// ** @param		command		The array of strings that contains the command
// ** @return		-1 on exit, 0 if it's not a builtin, 1 otherwise
// */

// static int		check_builtins(char **command)
// {
// 	if (ft_strequ(command[0], "exit"))
// 		return (-1);
// 	else if (ft_strequ(command[0], "echo"))
// 		return (echo_builtin(command + 1));
// 	else if (ft_strequ(command[0], "cd"))
// 		return (cd_builtin(command + 1));
// 	else if (ft_strequ(command[0], "setenv"))
// 		return (setenv_builtin(command + 1));
// 	else if (ft_strequ(command[0], "unsetenv"))
// 		return (unsetenv_builtin(command + 1));
// 	else if (ft_strequ(command[0], "env"))
// 	{
// 		print_env();
// 		return (1);
// 	}
// 	return (0);
// }

// /*
// ** Checks if the path is a regular file and is an executable, if it is,
// ** it executes it, if not, it prints an error on the screen then it returns
// ** whether it executed successfully or not
// **
// ** @param		bin_path	The path to search for
// ** @param		f			The path information from stat/lstat
// ** @param		command		The array of strings containing each word from the
// ** 							input
// ** @return		0 if the first path is not an executable or if the command
// ** 				was not executed properly or 1 for the opposite
// */

// static int		is_executable(char *bin_path, struct stat f, char **command)
// {
// 	if (f.st_mode & S_IFREG)
// 	{
// 		if (f.st_mode & S_IXUSR)
// 			return (run_cmd(bin_path, command));
// 		else
// 		{
// 			ft_putstr("minishell: permission denied: ");
// 			ft_putendl(bin_path);
// 		}
// 		free(bin_path);
// 		return (1);
// 	}
// 	free(bin_path);
// 	return (0);
// }

// /*
// ** Uses the first word of the input to search for an existing executable on the
// ** system, executes it if it found it and returns whether it found it or not
// **
// ** @param		command		The array of strings containing each word from the
// ** 							input
// ** @param		path		The value of the PATH environment variable
// ** @return		0 if the first word is not an executable or if the command was
// **				not executed properly or 1 for the opposite
// */

// static int		check_bins(char **command)
// {
// 	int				i;
// 	char			*bin_path;
// 	char			**path;
// 	struct stat		f;

// 	path = ft_strsplit(get_env_var("PATH"), ':');
// 	i = -1;
// 	while (path && path[++i])
// 	{
// 		if (ft_strstartswith(command[0], path[i]))
// 			bin_path = ft_strdup(command[0]);
// 		else
// 			bin_path = ft_pathjoin(path[i], command[0]);
// 		if (lstat(bin_path, &f) == -1)
// 			free(bin_path);
// 		else
// 		{
// 			ft_freestrarr(path);
// 			return (is_executable(bin_path, f, command));
// 		}
// 	}
// 	ft_freestrarr(path);
// 	return (0);
// }

// /*
// ** Executes a command and prints the result on the screen then returns whether
// ** there was a an exit or not
// ** The steps are:
// **		1. Check if it's a builtin command, if not...
// **		2. Check if it's a system command, if not ...
// **		3. Check if it's a folder or an executable, if not...
// **		4. Display an error (not found) message.
// **
// ** @param		command		The command to execute
// ** @return		-1 if there was an interruption (exit) or 0/1 if not
// */

// int				exec_command(char **command)
// {
// 	struct stat	f;
// 	int			is_builtin;

// 	if ((is_builtin = check_builtins(command)) == 1 || check_bins(command))
// 		return (0);
// 	if (is_builtin < 0)
// 		return (-1);
// 	if (lstat(command[0], &f) != -1)
// 	{
// 		if (f.st_mode & S_IFDIR)
// 		{
// 			change_dir(command[0], 0);
// 			return (0);
// 		}
// 		else if (f.st_mode & S_IXUSR)
// 			return (run_cmd(ft_strdup(command[0]), command));
// 	}
// 	ft_putstr("minishell: command not found: ");
// 	ft_putendl(command[0]);
// 	return (0);
// }