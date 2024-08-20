/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/20 18:09:29 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  execution_cmd(t_command 	*list ,char **new, char **env)
{

		char *ptr ;
		int pid = fork();
		if(pid < 0)
			perror("fork");
		else if(pid == 0)
		{
			if (new[0][0] == '/')
				ptr = new[0];
			else
				ptr = path_command(new[0]);
			if (!ptr)
			{
				hundle_redirections(list);	
				exit(127);
			}
			hundle_redirections(list);	
			if(execve(ptr, new , env) == -1)
				perror("execve");
			if (access(ptr, X_OK) == -1)
				exit(126);
		}
		else
		{
			int status;
			if(wait(&status) == -1)
				perror("wait");
		}
}


int		hundle_redirections(t_command *list)
{
	t_redirect *tmp;
	int		redir = 0;
	
	tmp = list->doc;
	printf("list->content ==========//////=============  %s\n", list->content);
	
	while (tmp != NULL)
	{
		if (tmp->type == REDIR_OUT)
		{
			hundle_redir_out(tmp->store);
			redir = 1;
		}
		if (tmp->type == REDIR_IN)
		{
			hundle_redir_in(tmp->store);
			redir = 1;
		}
		if( tmp->type == DREDIR_OUT)
		{
			hundle_dredir_out(tmp->store);
			redir = 1;
		}

		tmp = tmp->next;
	}
	list= list->next;
return (redir);
}

void  ft_exute( t_envarment *var , t_command *list , char **env)
{
		printf("***************************************************************\n");
		printf("**************    \033[0;31m   Result of the Command   \033[0m******************\n");
		printf("***************************************************************\n\n");
		
	if (list == NULL)
		return ;
	
	if(ft_strcmp(list->content , "exit") == 0)
		ft_exit(var , list);
		
	else if(ft_strcmp(list->content, "cd") == 0)
		ft_cd(list);
		
	else if (ft_strcmp(list->content, "pwd") == 0)
		ft_pwd(list);
		
	else if(ft_strcmp(list->content, "export") == 0)
		ft_export(var , list );
		
	else if(ft_strcmp(list->content, "unset") == 0)
		ft_unset(var , list );

	else if(ft_strcmp(list->content, "env") == 0)
		ft_env(var);
		
	else if(ft_strcmp(list->content, "echo") == 0)
		ft_echo(list,env);	
	else
	{
		if(herdoc_exist(list) == 1)
		{
			handle_here_doc(list,env);
		}
		if( pipe_exist(list) == 1)
		{
			handle_pipe(list, env);
		}
		else
		{

			char **new = ft_new_args(list->arg, list->doc);
			printf("new[0] = %s\n", new[0]);
			execution_cmd(list, new ,env);
		}
	}
}
