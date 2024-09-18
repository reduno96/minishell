/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:19:45 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/18 15:47:36 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"
t_envarment 	*find_env(t_envarment *my_var, char *old)
{
	if (my_var == NULL || old == NULL)
		return NULL;
	
	while (my_var)
	{
		if(ft_strcmp(my_var->var, old) == 0)
			return my_var;
		my_var = my_var->next;
	}
	return NULL;
}
void            ft_setenv_list(t_envarment **var ,char *old,  char **env)
{
	t_envarment *my_var;
	t_envarment *my_var_1;
    char        *path;

    
    my_var = *var;
	my_var_1 = *var;
    
	my_var = find_env(*var , old);
	if(my_var != NULL)
	{
		free(my_var->data);
		my_var->data = ft_strdup(ft_getenv("PWD", env));
	}
    my_var_1 = find_env(*var , "PWD");
	if(my_var_1 != NULL)
	{
		free(my_var_1->data);
        if( (path = getcwd(NULL, 0)) != NULL)
        {
		    my_var_1->data = ft_strdup(path);
            free(path);
        }
	}
}

  void  printf_error_cd(char *s)
{
        g_exit_status = 1;
        ft_putstr_fd(s, 2);
        ft_putchar_fd('\n', 2);
}

void complete_cd_1(t_envarment **var ,char *path, char **env)
{
(void )var;
    if (ft_strcmp(path, "--") == 0)
    {
        path = ft_getenv("HOME", env);
        if (chdir(path) == -1)
            printf_error_cd("cd: HOME not set");
    }
    else if (path[0] == '-' && path[1] == '\0')
    {
        path = ft_getenv("OLDPWD", env);
        if (path == NULL)
            printf_error_cd("cd: OLDPWD not set");
        else
        {
            chdir(path);
            printf("%s\n", path);
        }
    }
    else
        if (chdir(path) == -1)
        {
            g_exit_status = 1;
            perror("cd");
        }
}
void         complete_cd(char *path, char *ptr , char **env)
{  
    path = ft_getenv("HOME", env);
    if(ptr[1] == '/')
        path = ft_strjoin_1(path,ft_strchr(ptr,'/'));
        
    // printf("..............      %c      %s\n", ptr[1], path);
    if (path == NULL)
        printf_error_cd("cd: HOME not set");
    else
        if (chdir(path) == -1)
        {
            g_exit_status = 1;
            perror("cd");
        }
}

void ft_cd(t_envarment **var ,t_command *list, char **env)
{   
    char *path;
	
    if (list->arg[1] == NULL || list->arg[1][0] == '\0')
    {
        path = ft_getenv("HOME", env);
        if (path == NULL)
            printf_error_cd("cd: HOME not set");
        else
             if (chdir(path) == -1)
            {
                g_exit_status = 1;
                perror("cd");
            }
    }
    else
    {
        path = list->arg[1];
        if (path[0] == '~')
            complete_cd(path, list->arg[1] ,env);
            
        else
            complete_cd_1(var,path, env);
    }
    ft_setenv_list(var ,"OLDPWD", env );
}
