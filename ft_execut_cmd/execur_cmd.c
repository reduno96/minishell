/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execur_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:31:58 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/19 13:41:59 by bouhammo         ###   ########.fr       */
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



char    *command_execut(t_command *list)
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

void    close_free_wait( int *pids, int **pipefd, int num_cmd , t_command *tmp_cmd)
{
    int i ;
    int j;
    int status;

    close(pipefd[num_cmd - 1][0]);
    close(pipefd[num_cmd - 1][1]);
    j=0;
    while(j < num_cmd)
    {
        if (waitpid(pids[j], &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        j++;
    }
    i=0;
    free(pids);
    while (i < num_cmd - 1)
    {
        free(pipefd[i]);
        i++;
    }
    free(pipefd);
    free(tmp_cmd);
}
void           child_process(int ** pipefd,int  i,t_command *tmp_cmd,char **env , int num_cmd)
{
        char **new_args ;
        char *ptr;
        
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
        new_args = ft_new_args(tmp_cmd->arg , tmp_cmd->doc);
        ptr = command_execut(tmp_cmd);
        if (!ptr) exit(EXIT_FAILURE);
        execve(ptr, new_args, env);
        perror("execve failed");
        exit(EXIT_FAILURE);
}



void handle_pipe(t_command *list, char **env)
{
    int num_cmd = num_pipe(list) + 1;
    int **pipefd = return_pipe(num_cmd);
    pid_t *pids = (pid_t *)malloc(sizeof(pid_t) * num_cmd);
    
    if (!pids) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    t_command *tmp_cmd = get_list_command(list);
    
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
             child_process(pipefd, i, tmp_cmd, env , num_cmd);
        }
        if (i > 0) {
            close(pipefd[i - 1][0]);
            close(pipefd[i - 1][1]);
        }

        tmp_cmd = tmp_cmd->next;
        i++;
    }
    close_free_wait(pids, pipefd, num_cmd , tmp_cmd);   
}









