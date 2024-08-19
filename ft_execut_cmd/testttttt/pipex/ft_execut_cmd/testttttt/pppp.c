#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2]; // Array to hold pipe descriptors
    pid_t pid;
    char write_msg[] = "Hello, child process!";
    char read_msg[100];

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // Create a child process using fork
    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

