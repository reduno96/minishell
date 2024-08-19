/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:46:31 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/19 12:34:02 by bouhammo         ###   ########.fr       */
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


bool		hundle_redirections(t_command *list)
{
	t_redirect *tmp;
	bool		redir = false;
	
	tmp = list->doc;
	while (tmp != NULL)
	{
		if (tmp->type == REDIR_OUT)
		{
			hundle_redir_out(tmp->store);
			redir = true;
		}
		else if (tmp->type == REDIR_IN)
		{
			hundle_redir_in(tmp->store);
			redir = true;
		}
		else if ( tmp->type == DREDIR_OUT)
		{
			hundle_dredir_out(tmp->store);
			redir = true;
		}
		// else if ( tmp->doc->type == HERE_DOC)
		// {
		// 	printf("\n************************** Redirections HERDOG  | %s \n", tmp->doc->store);

		// }
		tmp = tmp->next;
	}
	return (redir);
}

void  ft_exute( t_envarment *var , t_command *list , char **env)
{
	if (list == NULL)
		return ;
	
	if(ft_strcmp(list->content , "exit") == 0)
		exit(0);
		
	else if(ft_strcmp(list->content, "cd") == 0)
		ft_cd(list);
		
	else if (ft_strcmp(list->content, "pwd") == 0)
		ft_pwd(list);
		
	else if(ft_strcmp(list->content, "export") == 0)
		ft_export(var , list );
		
	else if(ft_strcmp(list->content, "unset") == 0)
		ft_unset(var , list );

	else if(ft_strcmp(list->content, "env") == 0)
		ft_env(var );
		
	else if(ft_strcmp(list->content, "echo") == 0)
		ft_echo(list,env);	
	else
	{
		printf("***************************************************************\n");
		printf("**************       Result of the Command     ****************\n");
		printf("***************************************************************\n\n");

		if( pipe_exist(list) == 1)
		{
			// hundle_redirections(list);
			handle_pipe(list,env);
		}
		else
		{
			char **new = ft_new_args(list->arg, list->doc);
			execution_cmd(list, new ,env);
		}
	}
}
