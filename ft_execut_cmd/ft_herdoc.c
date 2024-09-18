/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/18 13:13:12 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	herdoc_exist(t_command *list)
{
	t_command	*tmp;
	int 		count;

	if (list == NULL)
		return (0);
	count =0;
	tmp = list;
	count = count_herdoc(tmp);
	if( count != 0)
		return 1;
	else
		return 0;
}


char *ft_handle_var(char *line, int *i, t_envarment *my_env, char *final)
{
    int len = 0;
    int j;
    char *s;

    (*i)++;
    j = *i;
    while (line[*i] && ft_isalnum(line[*i]))
    {
        (*i)++;
        len++;
    }
	(*i)--;
	j--;
	len++;
    s = ft_expand(ft_substr(line, j, len), &my_env);
    final = ft_strjoin(final, s);
    free(s);
    return final;
}


char *ft_expand_in_her(char *line, t_envarment *my_env)
{
    int i = 0;
    int j;
    int len;
    char *final = NULL;

    while (line[i])
    {
        len = 0;
        if (line[i] == '$')
            final = ft_handle_var(line, &i, my_env, final);
        else
        {
            j = i;
            while (line[i] && line[i] != '$')
            {
                i++;
                len++;
            }
            final = ft_strjoin_1(final, ft_substr(line, j, len));
			i--;
        }
		i++;
    }
    return final;
}


// char	*ft_expand_in_her(char *line, t_envarment *my_env)
// {
// 	int i = 0;
// 	int len = 0;
// 	int j = 0;
// 	char *s;
// 	char *final;

// 	final = NULL;
// 	while (line[i])
// 	{
// 		len = 0;
// 		if (line[i] == '$')
// 		{
// 			i++;
// 			j = i;
// 			while (line[i] && ft_isalnum(line[i]))
// 			{
// 				i++;
// 				len++;
// 			}
// 			i--;
// 			j--;
// 			len++;
// 			s = ft_expand(ft_substr(line, j, len), &my_env);
// 			final = ft_strjoin(final, s);
// 			free(s);
// 		}
// 		else
// 		{
// 			j = i;
// 			while (line[i] && line[i] != '$')
// 			{
// 				i++;
// 				len++;
// 			}
// 			final = ft_strjoin_1(final, ft_substr(line, j, len));
// 			i--;
// 		}
// 		i++;

// 	}
// 	return (final);
// }




void	write_in_file(t_here_doc *tmp, char *line, t_envarment **var)
{
	char		*tmp_line;
	char		*path_file;
	char 		*final;
	t_envarment *my_env;
	char 		*itoa;

	my_env  = *var;
	final = NULL;

	itoa = ft_itoa(tmp->idx);
	tmp_line = ft_strjoin_1(tmp->store, itoa);
	path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
	free(tmp_line);
	free(itoa);

	
	tmp->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp->fd < 0)
	{
		perror("open");
		return ;
	}
	if (tmp->expad == 1)
	{
		final = ft_expand_in_her(line, my_env);
		ft_putstr_fd(final, tmp->fd);
	}
	else
		ft_putstr_fd(line, tmp->fd);
	free(line);
	free(path_file);
	write(tmp->fd, "\n", 1);
	close(tmp->fd);
}

int	count_herdoc(t_command *tmp)
{
	int			count;
	t_command	*cmd;
	t_here_doc	*her ;

	cmd = tmp;
	count = 0;
	if (tmp == NULL )
		return (0);
	while (cmd != NULL)
	{
		her = cmd->her;
		if (her != NULL)
		{
			while (her != NULL)
			{
				if (her->store != NULL)
					count++;
				her = her->next;
			}
			cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
	return (count);
}

void	sig_herdoc(int sig)
{
	(void)sig;
	printf("\n");
	// sleep(1);
	exit(1);
}

void hundle_chil_pro(t_here_doc *tmp_her ,t_envarment **var )
{
	char *line;

	signal(SIGINT , sig_herdoc);
	signal(SIGQUIT , SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (line == NULL )
			exit(EXIT_SUCCESS);

		if (ft_strcmp(line, tmp_her->store) == 0)
			exit(EXIT_SUCCESS);
		else
			write_in_file(tmp_her, line, var);
	}
}

int handle_fork( t_here_doc *tmp_her , t_envarment **var)
{
    int pid;
    int status = -1;
	void (*old_sigint_handler)(int);
	
	old_sigint_handler = signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			signal(SIGINT,old_sigint_handler);
			return 0;
		}
		if (pid == 0)
		{
			hundle_chil_pro(tmp_her,var);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
				g_exit_status = status;
			
		}
	return status;
}

int    ft_cmp_delimeter(t_command *tmp_cmd, t_envarment **var)
{
    t_here_doc *tmp_her;
  
    int status = -1;

    tmp_her = tmp_cmd->her;
    while (tmp_cmd != NULL && tmp_her != NULL)
	{
		status = handle_fork(tmp_her , var);
		if (status == 256)
				return status;
		tmp_her = tmp_her->next;
    }
	return status;
}




// int    ft_cmp_delimeter(t_command *tmp_cmd, t_envarment **var)
// {
//     t_here_doc *tmp_her;
//     char *line;
//     int pid;
//     int status = -1;
// 	void (*old_sigint_handler)(int);

//     tmp_her = tmp_cmd->her;
//     while (tmp_cmd != NULL && tmp_her != NULL)
// 	{

// 		old_sigint_handler = signal(SIGINT, SIG_IGN);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			perror("fork");
// 			signal(SIGINT,old_sigint_handler);
// 			return 0;
// 		}
// 		if (pid == 0)
// 		{
// 			signal(SIGINT , sig_herdoc);
// 			signal(SIGQUIT , SIG_IGN);
// 			while (1)
// 			{
// 				line = readline("> ");
// 				if (line == NULL )
// 					exit(EXIT_SUCCESS);

// 				if (ft_strcmp(line, tmp_her->store) == 0)
// 					exit(EXIT_SUCCESS);
// 				else
// 					write_in_file(tmp_her, line, var);
// 			}
// 		}
// 		else
// 		{
// 			waitpid(pid, &status, 0);
// 			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
// 				g_exit_status = status;
// 			if (status == 256)
// 				return status;
// 			tmp_her = tmp_her->next;
// 		}
//     }
// 	return status;
// }


void 	create_files(t_command *cmd)
{
	t_command	*tmp;
	t_here_doc	*tmp_her;
	char		*tmp_line;
	char		*path_file;
	char  		*itoa;

	if(cmd == NULL)
		return ;
	tmp = cmd;
	while (tmp != NULL)
	{
		tmp_her = tmp->her;
		while (tmp != NULL && tmp_her != NULL)
		{
			itoa = ft_itoa(tmp_her->idx);
			tmp_line = ft_strjoin_1(tmp_her->store ,itoa );
			free(itoa);
			path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
			free(tmp_line);
			tmp_her->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
			free(path_file);
			close(tmp_her->fd);
			tmp_her = tmp_her->next;
		}
		tmp = tmp->next;
	}
}
void 	exit_herdoc(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

void 	delet_files(t_command *cmd)
{
	t_command *tmp;
	t_here_doc *her;
	char *ptr;
	char *file;
	
	tmp = cmd;
	while (tmp != NULL)
	{
		her = tmp->her;
		while (her != NULL)
		{

			ptr = ft_strjoin(her->store ,ft_itoa(her->idx));
			free(ft_itoa(her->idx));
			file = ft_join( "/tmp/herdoc" ,ptr);
			free(ptr);
			if(unlink(file) != 0)
			{
				g_exit_status = 1;
				perror("");
			}
			free(file);
			her = her->next;
		}
		tmp = tmp->next;
	}
}
void 	handle_here_doc(t_envarment **var ,t_command *cmd )
{
	t_command	*tmp_cmd;
	int			status;
	
	tmp_cmd = cmd;
	if (cmd == NULL || tmp_cmd == NULL)
		return ;

	create_files(tmp_cmd);
	while (tmp_cmd != NULL)
	{
		status = ft_cmp_delimeter(tmp_cmd,  var);
		if (status == 256 )
			break;
		tmp_cmd = tmp_cmd->next;
	}
}

