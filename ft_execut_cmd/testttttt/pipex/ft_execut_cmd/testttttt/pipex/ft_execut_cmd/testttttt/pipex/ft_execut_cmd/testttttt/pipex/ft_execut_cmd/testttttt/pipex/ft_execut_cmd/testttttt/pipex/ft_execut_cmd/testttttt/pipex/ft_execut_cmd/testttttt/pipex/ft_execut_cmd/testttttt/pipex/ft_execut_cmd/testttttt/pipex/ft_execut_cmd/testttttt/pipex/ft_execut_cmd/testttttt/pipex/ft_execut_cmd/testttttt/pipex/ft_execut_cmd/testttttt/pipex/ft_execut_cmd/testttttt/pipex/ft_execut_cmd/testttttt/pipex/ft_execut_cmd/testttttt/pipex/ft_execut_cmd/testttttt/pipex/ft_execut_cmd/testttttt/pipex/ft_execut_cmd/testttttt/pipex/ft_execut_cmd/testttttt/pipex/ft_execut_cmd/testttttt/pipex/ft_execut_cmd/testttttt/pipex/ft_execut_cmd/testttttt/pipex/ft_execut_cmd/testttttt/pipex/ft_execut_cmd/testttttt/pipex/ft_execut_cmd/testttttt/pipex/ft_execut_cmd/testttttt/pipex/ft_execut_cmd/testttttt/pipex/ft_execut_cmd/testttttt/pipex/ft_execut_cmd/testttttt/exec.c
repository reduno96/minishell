#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void handle_redirection(t_command *list)
{
    t_redirect *redir = list->doc;
    while (redir)
    {
        if (redir->type == REDIR_OUT)
        {
            int fd = open(redir->store, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
            {
                perror("open");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0)
            {
                perror("dup2");
                exit(1);
            }
            close(fd);
        }
        // Add handling for other redirection types (e.g., REDIR_IN, DREDIR_OUT, etc.) here
        redir = redir->next;
    }
}

void execute_command(t_command *list, char **env)
{
    char *ptr;
    int pid = fork();
    
    if (pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        // Child process: Handle redirection and execute the command
        handle_redirection(list);
        
        if (list->arg[0][0] == '/')
            ptr = list->arg[0];
        else
            ptr = path_command(list->arg[0]);
        
        if (!ptr)
        {
            printf("\033[1;33mcommand not found\n\033[0m");
            exit(127);
        }
        
        if (execve(ptr, list->arg, env) == -1)
        {
            perror("execve");
            exit(1);
        }
        
        if (access(ptr, X_OK) == -1)
            exit(126);
    }
    else
    {
        // Parent process
        int status;
        if (wait(&status) == -1)
        {
            perror("wait");
        }
    }
}

void hundle_command(t_command *list, char **env)
{
    if (pipe_exist(list) == 0)
    {
        printf("\n\n No pipe\n\n");
        execute_command(list, env);
    }
    else
    {
        printf("\n\n Yes pipe\n\n");
        // Handle pipe logic here
    }
}

void ft_execute(t_envarment *var, t_command *list, char **env)
{
    if (list == NULL)
        return;
    
    if (ft_strcmp(list->content, "exit") == 0)
        exit(0);
    else if (ft_strcmp(list->content, "cd") == 0)
        ft_cd(list);
    else if (ft_strcmp(list->content, "pwd") == 0)
        ft_pwd(list);
    else if (ft_strcmp(list->content, "export") == 0)
        ft_export(var, list);
    else if (ft_strcmp(list->content, "unset") == 0)
        ft_unset(var, list);
    else if (ft_strcmp(list->content, "env") == 0)
        ft_env(var);
    else if (ft_strcmp(list->content, "echo") == 0)
        ft_echo(list);
    else
    {
        hundle_command(list, env);
    }
}
:!

