#include <unistd.h>
#include <stdio.h>

int main()
{
	char *cmd= {"grep" , "-E",     "c$" , "-", 0};
	char *bin_file = cmd[0];

	if(execvp(bin_file , cmd ) == -1)
			fprintf(stderr , "Error executing %s\n", bin_file);

printf("done\n");
	return 0;
}

// void handle_pipe(t_command *list, char **env)
// {


//     int status;
//     int pipefd[2];
//     pid_t pid1, pid2;

//     // Create a pipe
//     if (pipe(pipefd) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // First child process for 'ls'
//     pid1 = fork();
//     if (pid1 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid1 == 0) {
//         // Child 1: 'ls'
//         // Close the read end of the pipe
//         close(pipefd[0]);

//         // Redirect stdout to the write end of the pipe
//         dup2(pipefd[1], STDOUT_FILENO);

//         // Close the write end of the pipe
//         close(pipefd[1]);

//         printf("--------------------------------+****-------------------------\n\n");
//         char *str = command_execut(list);
//         printf("str  ++++++++++++++++++ = %s\n\n", str);  
//         execve(str, list->arg, env);
//         // list = list->next;
//         perror("execlp ls");
//         exit(EXIT_FAILURE);
//     }

//     // Second child process for 'wc'
//     pid2 = fork();
//     if (pid2 == -1) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }

//     if (pid2 == 0) {
//         // Child 2: 'wc'
//         // Close the write end of the pipe
//         close(pipefd[1]);

//         // Redirect stdin to the read end of the pipe
//         dup2(pipefd[0], STDIN_FILENO);

//         // Close the read end of the pipe
//         close(pipefd[0]);

//         // Execute 'wc'
//         char *ptr = command_execut(list);
//         printf("ptr  ++++++++++++++++++======================= = %s\n\n", ptr);
        
//         execve( ptr, list->arg, env);
//         perror("execlp wc");
//         exit(EXIT_FAILURE);
//     }

//     // Parent process
//     // Close both ends of the pipe, as they're no longer needed
//     close(pipefd[0]);
//     close(pipefd[1]);

//     // Wait for both child processes to finish
//      if (wait(&status) == -1) {
//         perror("wait");
//         exit(EXIT_FAILURE);
//     }
    
//     if (wait(&status) == -1) {
//         perror("wait");
//         exit(EXIT_FAILURE);
//     }
// }


// void handle_pipe(t_command *list, char **env)
// {
// 	printf("\n ***************** handle_pipe\n");
// 	(void)env;
// 	int mult_pipe = num_pipe(list);
//     int pipefd[mult_pipe - 1][2]; // Pipes between commands
//     pid_t pid[mult_pipe]; // Array to store PIDs of child processes

//     // Create pipes
//     for (int i = 0; i < mult_pipe - 1; i++) {
//         if (pipe(pipefd[i]) == -1) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Create child processes for each command
//     for (int i = 0; i < mult_pipe; i++) {
//         pid[i] = fork();

//         if (pid[i] == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }

//         if (pid[i] == 0) { // Child process
//             // If not the first command, get input from the previous pipe
//             if (i > 0) {
//                 dup2(pipefd[i - 1][0], STDIN_FILENO);
//             }
//             // If not the last command, output to the next pipe
//             if (i < mult_pipe - 1) {
//                 dup2(pipefd[i][1], STDOUT_FILENO);
//             }

//             // Close all pipe ends in child
//             for (int j = 0; j < mult_pipe - 1; j++) {
//                 close(pipefd[j][0]);
//                 close(pipefd[j][1]);
//             }

//             char *str = command_execut(list);
//             // printf("list->content  ++++++++++++++++++ = %s\n\n", str);
// 			list = list->next;
//             // str = command_execut(list);

//             // printf("list->content  ++++++++++++++++++ = %s\n\n", str);
//             execvp(str,  list->arg);

//             perror("execvp");
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Close all pipe ends in parent
//     for (int i = 0; i < mult_pipe - 1; i++) {
//         close(pipefd[i][0]);
//         close(pipefd[i][1]);
//     }

//     // Wait for all child processes to finish
//     for (int i = 0; i < mult_pipe; i++) {
//         waitpid(pid[i], NULL, 0);
//     }
// }

// void handle_pipe(t_command *list, char **env)
// {
// 	int mult_pipe = num_pipe(list);
// 	int i = 0;
// 	int pipefd[2];
// 	int prev_fd = 0;

// 	printf("Number of pipes = %d\n", mult_pipe);

// 	while (i < mult_pipe && list)
// 	{
// 		if (i < mult_pipe - 1)
// 		{
// 			if (pipe(pipefd) == -1)
// 			{
// 				perror("pipe");
// 				exit(EXIT_FAILURE);
// 			}
// 		}

// 		pid_t pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}

// 		if (pid == 0) // Child process
// 		{
// 			if (i > 0)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			if (i < mult_pipe - 1)
// 			{
// 				dup2(pipefd[1], STDOUT_FILENO);
// 				close(pipefd[0]);
// 				close(pipefd[1]);
// 			}
// 			printf(" list->content ***************  = %s\n", list->content);
// 			execve(list->content, list->arg, env);
// 				perror("execve \n"); // In case execve fails
// 			list = list->next;
// 			exit(EXIT_FAILURE);
// 		}
// 		else // Parent process
// 		{
// 			if (i < mult_pipe - 1)
// 			{
// 				close(pipefd[1]);
// 			}
// 			if (i > 0)
// 			{
// 				close(prev_fd);
// 			}
// 			if (i < mult_pipe - 1)
// 			{
// 				prev_fd = pipefd[0];
// 			}
// 		}

// 		i++;
// 		list = list->next;
// 	}

// 	i = 0;
// 	while (i < mult_pipe)
// 	{
// 		int status;
// 		if (wait(&status) == -1)
// 		{
// 			perror("wait");
// 		}
// 		i++;
// 	}
// }
// void		handle_pipe( t_command *list, char **env)
// {
// 	(void)env;
// 	int mult_pipe = num_pipe(list)+1;	
// 	// u = num_pipe(list);
// 	printf(" number of the pipe is  = %d\n",mult_pipe);
	
// 	int i = 0;
// 	int pipefd[2];
// 	int prev_fd = 0;
// 	while (i < mult_pipe && list)
// 	{
// 		printf("iiiiiiiiiiiiiiiiiii = %d  mu= %d \n ",i, mult_pipe);
// 		if(i < mult_pipe )//-1)
// 		{
// 				printf("Create Pipe    \n");

// 			if (pipe(pipefd) == -1)
// 			{
// 				perror("pipe");
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 		pid_t pid = fork();
// 		if(pid == -1)
// 		{
// 			perror("fork");
// 			exit(EXIT_FAILURE);
// 		}
// 		if(pid == 0)
// 		{
// 			if(i > 0)
// 			{
// 				dup2(prev_fd , STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			if(i < mult_pipe -1)
// 			{
// 				dup2(pipefd[1], STDOUT_FILENO);
// 				close(pipefd[0]);
// 				close(pipefd[1]);
// 			}
// 			printf("+++++++++++++++++++++++++++++++++++++++++\n\n");
// 			execve(list->content, list->arg , env);
// 			// cmd(list, list->arg ,env);
			
// 			printf("\n\n 1 list->content = %s \n", list->content);
// 			int j = 0;
// 			while (list->arg[j])
// 			{
// 				printf("list->content[j] = %s\n", list->arg[j]);
// 				j++;
// 			}
// 			if(list->content[0] == '|')
// 			{
// 				printf("OK\n");
// 			}
// 			// list = list->next;	
// 			printf("\n\n 2 list->content = %s \n", list->content);
		
// 			// if(list->content[0] == '|')
// 			// 	list = list->next->ne;
//             exit(EXIT_FAILURE);

// 		}
// 		else
// 		{
// 			printf("Parent Process i = %d\n\n\n", i);
// 			if( i < mult_pipe -1 )
// 			{
// 				close(pipefd[1]);
// 			}
// 			if(i > 0)
// 			{
// 				close(prev_fd);
// 			}
// 			if(i < mult_pipe -1)
// 			{
// 				prev_fd = pipefd[0];
// 			}
// 		}
// 		i++;
// 		list = list->next;
		
// 	}
// 	 i =0;
// 	 while (i < mult_pipe)
// 	 {
// 		int status;
// 		if(wait(&status) == -1)
// 			perror("wait");
// 		 i++;
// 	 }
	 
	

	
	
	
	
// 	// while (i < mult_pipe + 1)
// 	// {
		
// 	// }
// }





// ///////////////////////////
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//     int num_cmds = 3; // Number of commands
//     char *cmds[3][3] = {
//         {"CMD1", "arg1", NULL},
//         {"CMD2", "arg2", NULL},
//         {"CMD3", "arg3", NULL}
//     };

//     int pipefd[2];
//     int prev_fd = 0; // Initially, the previous file descriptor is stdin (0)

//     for (int i = 0; i < num_cmds; i++) {
//         // Create a pipe, except for the last command
//         if (i < num_cmds - 1) {
//             if (pipe(pipefd) == -1) {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         }

//         // Fork the process
//         pid_t pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }

//         if (pid == 0) { // Child process
//             // If not the first command, set the input from the previous pipe
//             if (i > 0) {
//                 dup2(prev_fd, STDIN_FILENO);
//                 close(prev_fd);
//             }

//             // If not the last command, set the output to the current pipe
//             if (i < num_cmds - 1) {
//                 dup2(pipefd[1], STDOUT_FILENO);
//                 close(pipefd[0]);
//                 close(pipefd[1]);
//             }

//             // Execute the command
//             execvp(cmds[i][0], cmds[i]);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         } else { // Parent process
//             // Close the write end of the current pipe in the parent
//             if (i < num_cmds - 1) {
//                 close(pipefd[1]);
//             }

//             // Close the previous file descriptor if it's not stdin
//             if (i > 0) {
//                 close(prev_fd);
//             }

//             // Store the read end of the pipe for the next iteration
//             if (i < num_cmds - 1) {
//                 prev_fd = pipefd[0];
//             }
//         }
//     }

//     // Wait for all child processes
//     for (int i = 0; i < num_cmds; i++) {
//         wait(NULL);
//     }

//     return 0;
// }

