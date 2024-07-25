#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 1024

int	main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_COMMAND_LENGTH / 2];
		// Assuming arguments are shorter than commands
	int arg_count = 0;

	while (1)
	{
		printf("simple_shell> ");
		fgets(command, MAX_COMMAND_LENGTH, stdin);

		// Remove trailing newline
		command[strcspn(command, "\n")] = 0;

		// Check for exit command
		if (strcmp(command, "exit") == 0)
		{
			break ;
		}

		// Tokenize the command into arguments
		args[arg_count++] = strtok(command, " ");
		while ((args[arg_count] = strtok(NULL, " ")) != NULL)
		{
			arg_count++;
		}

		// Fork a child process
		pid_t pid = fork();

		if (pid == 0)
		{ // Child process
			// Execute the command using execvp
			if (execvp(args[0], args) == -1)
			{
				perror("execvp failed");
				exit(1);
			}
		}
		else if (pid > 0)
		{ // Parent process
			// Wait for child process to finish
			wait(NULL);
		}
		else
		{ // Fork failed
			perror("fork failed");
			exit(1);
		}

		arg_count = 0; // Reset argument count
	}

	printf("Exiting shell...\n");
	return (0);
}