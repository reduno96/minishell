/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execur_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:58 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/19 13:25:03 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pipe_exist(t_command *list)
{
	t_command *tmp ;

	tmp = list;
	while (tmp)
	{
		if (tmp->content[0] == '|')
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int  	num_pipe(t_command *list)
{
	t_command *tmp;
	tmp = list;
	int i=0;
	while (tmp)
	{
		if (tmp->content[0] == '|')
			i++;
		tmp = tmp->next;
	}
	return (i);
}



char *command_execut(t_command *list)
{
    if (list == NULL) {
        fprintf(stderr, "Error: Command not found\n");
        return NULL;
    }

    char *ptr = path_command(list->content);
    if (!ptr)
        perror("Error: Command not found");

    return ptr;
}



int **return_pipe(int num_cmd)
{
    int **pipe;
    int i;
    pipe = (int **)malloc(sizeof(int*) * num_cmd);
    if (!pipe) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(i < num_cmd)
    {
        pipe[i] = (int *)malloc(sizeof(int) * 2);
        if (!pipe[i]) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    return pipe;
}


t_command *get_list_command(t_command *list)
{
    t_command *tmp = NULL;
    t_command *head = NULL;
    t_command *prev = NULL;

    while (list)
    {
        if (list->content[0] == '|')
            list = list->next;
        else
        {
            tmp = (t_command *)malloc(sizeof(t_command));
            if (!tmp)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            tmp->content = list->content;
            tmp->arg = list->arg;
            tmp->doc = list->doc;
            tmp->next = NULL;
            if (prev)
                prev->next = tmp;
            else
                head = tmp;
            prev = tmp;
            list = list->next;
        }
    }
    return head;
}


void handle_pipe(t_command *list, char **env) 
{
    int num_cmd = num_pipe(list) + 1;
    int status;
    int **pipefd = return_pipe(num_cmd);
    pid_t *pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
    
    if (!pids) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    t_command *tmp_cmd = get_list_command(list);
    // while (tmp_cmd)
    // {
    //     printf("tmp_cmd = %s\n", tmp_cmd->content);
    //     int h = 0;
    //     while (tmp_cmd->arg[h])
    //     {
    //         printf("tmp_cmd->arg[%d] = %s\n", h, tmp_cmd->arg[h]);
    //         printf("tmp_cmd->doc[%d] = %s\n", h, tmp_cmd->doc->store);
    //         h++;
    //     }
        
        
    //     tmp_cmd = tmp_cmd->next;
    // }
    
    int i = 0;
    while (i < num_cmd && tmp_cmd)
    {
        if (pipe(pipefd[i]) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0)
        {        
            hundle_redirections(tmp_cmd);
    
            if (i > 0) 
            {
                close(pipefd[i - 1][1]);
                dup2(pipefd[i - 1][0], STDIN_FILENO);
                close(pipefd[i - 1][0]);
            }
            
            if (i < num_cmd - 1)
            {
                close(pipefd[i][0]);
                dup2(pipefd[i][1], STDOUT_FILENO);
                close(pipefd[i][1]);
            }
     
            char **new_args = ft_new_args(tmp_cmd->arg , tmp_cmd->doc);
            char *ptr = command_execut(tmp_cmd);
            if (!ptr) exit(EXIT_FAILURE);
            execve(ptr, new_args, env);
            perror("execve failed");
            exit(EXIT_FAILURE);
            
            // char *ptr = command_execut(tmp_cmd);
            // if (!ptr) exit(EXIT_FAILURE);
            // execve(ptr, tmp_cmd->arg, env);
            // perror("execve failed");
            // exit(EXIT_FAILURE);
        }

        if (i > 0) {
            close(pipefd[i - 1][0]);
            close(pipefd[i - 1][1]);
        }

        tmp_cmd = tmp_cmd->next;
        i++;
    }
    close(pipefd[num_cmd - 1][0]);
    close(pipefd[num_cmd - 1][1]);
    
    int j =0;
    while(j < num_cmd)
    {
        if (waitpid(pids[j], &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        j++;
    }

    free(pids);
    i = 0;
    while (i < num_cmd - 1)
    {
        free(pipefd[i]);
        i++;
    }
    free(pipefd);
    free(tmp_cmd);
}























//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

/*

void    child_process_1(pid_t pid1 , t_command *list, char **env, int pipefd[2])
{
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]); 

        char *str = command_execut(list);
        if (!str) exit(EXIT_FAILURE);

        execve(str, list->arg, env); 
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}
void    child_process_2(int pid2 ,t_command *list,char **env,int  pipefd[2])
{
    pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
       
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO); 
        close(pipefd[0]); 
        
        list = list->next; 
        char *ptr = command_execut(list);
        if (!ptr) exit(EXIT_FAILURE);

        list = list->next;

        execve(ptr, list->arg, env);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }
}

void handle_pipe_1(t_command *list, char **env) {
    int status;
    int pipefd[2];
    pid_t pid1=0, pid2=0;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    child_process_1(pid1 , list, env, pipefd);   
    child_process_2(pid2 , list, env, pipefd);
    
    close(pipefd[0]);
    close(pipefd[1]);


    if (waitpid(pid1, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    if (waitpid(pid2, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
}



*/
// void handle_pipe(t_command *list, char **env) 
// {

//     int num_cmd;
//     int status;
//     int  **pipefd;
//     pid_t *pids;
//     int i = 0;

//     num_cmd = num_pipe(list) +1;
//     pipefd = return_pipe(num_cmd);
//     pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
//     if (!pids) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }
//     printf("num_cmd = %d\n", num_cmd);
//     int j = 0;
//     while (j  < num_cmd)
//     {
//         printf("j = %d\n", j);
//         if (pipe(pipefd[j]) == -1)
//         {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }
//         j++;
//     }

        
//     while (i < num_cmd)
//     {
//         // if (i < num_cmd - 1) {
//         //     if (pipe(pipefd[i]) == -1) {
//         //         perror("pipe");
//         //         exit(EXIT_FAILURE);
//         //     }
//         // }
//         pids[i] = fork();
        
//         if( pids[i] == -1)
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         if(pids[i] == 0)
//         {
//             if (i == 0)
//             {

//                 close(pipefd[i][0]);
//                 dup2(pipefd[i][1] , STDOUT_FILENO);
//                 close(pipefd[i][1]);
                
//                 char *ptr = command_execut(list);
//                 if (!ptr) exit(EXIT_FAILURE);
                
//                 execve(ptr, list->arg, env);
//                 perror("execve failed");
//                 exit(EXIT_FAILURE);
//             }
//             else if (i == num_cmd - 1)
//             {                
//                 close(pipefd[i][1]);
//                 dup2(pipefd[i][0], STDIN_FILENO);
//                 close(pipefd[i][0]);

//                 list = list->next;

//                 char *str = command_execut(list);
//                 if (!str) exit(EXIT_FAILURE);
//                  list = list->next;
                 
//                 execve(str, list->arg, env);
//                 perror("execve failed");
//                 exit(EXIT_FAILURE);
//             }
//             else
//             {
//                 close(pipefd[i][0]);
//                 dup2(pipefd[i][1], STDOUT_FILENO);
//                 close(pipefd[i][1]);
                
//                 char *ptr = command_execut(list);
//                 if (!ptr) exit(EXIT_FAILURE);

//                 execve(ptr, list->arg, env);
//                 perror("execve failed");
//                 exit(EXIT_FAILURE);
//             }
//         }
//             if (waitpid(pids[i], &status, 0) == -1)
//             {
//                 perror("waitpid");
//                 exit(EXIT_FAILURE);
//             }
            
//             if (num_cmd > 1)
//             {
//                 close(pipefd[num_cmd - 2][0]);
//                 close(pipefd[num_cmd - 2][1]);
//             }
 
//     // Wait for all child processes
//     // for (int i = 0; i < num_cmd; i++) {
//         if (waitpid(pids[i+1], &status, 0) == -1) {
//             perror("waitpid");
//             exit(EXIT_FAILURE);
//         }
//     // }

//          i++;
// 	}
// }


// void handle_pipe(t_command *list, char **env) 
// {
//     int num_cmd = num_pipe(list) + 1;
//     int status;
//     int **pipefd = return_pipe(num_cmd);
//     pid_t *pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);

//     if (!pids) {
//         perror("malloc");
//         exit(EXIT_FAILURE);
//     }

//     for (int i = 0; i < num_cmd; i++) {
//         if (i < num_cmd - 1) {
//             if (pipe(pipefd[i]) == -1) {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         }

//         pids[i] = fork();
//         if (pids[i] == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }

//         if (pids[i] == 0) {  // Child process
//             if (i > 0) {
//                 dup2(pipefd[i - 1][0], STDIN_FILENO);
//                 close(pipefd[i - 1][0]);
//                 close(pipefd[i - 1][1]);
//             }

//             if (i < num_cmd - 1) {
//                 close(pipefd[i][0]);
//                 dup2(pipefd[i][1], STDOUT_FILENO);
//                 close(pipefd[i][1]);
//             }
//             list = list->next;

//             char *ptr = command_execut(list);
//             if (!ptr) exit(EXIT_FAILURE);
//             list = list->next;

//             execve(ptr, list->arg, env);
//             perror("execve failed");
//             exit(EXIT_FAILURE);
//         }

//         // Parent process: close used pipe ends
//         if (i > 0) {
//             close(pipefd[i - 1][0]);
//             close(pipefd[i - 1][1]);
//         }

//         list = list->next;
//     }

//     // Close the last pipe in the parent
//     if (num_cmd > 1) {
//         close(pipefd[num_cmd - 2][0]);
//         close(pipefd[num_cmd - 2][1]);
//     }

//     // Wait for all child processes
//     for (int i = 0; i < num_cmd; i++) {
//         if (waitpid(pids[i], &status, 0) == -1) {
//             perror("waitpid");
//             exit(EXIT_FAILURE);
//         }
//     }

//     free(pids);
//     for (int i = 0; i < num_cmd - 1; i++) {
//         free(pipefd[i]);
//     }
//     free(pipefd);
// }