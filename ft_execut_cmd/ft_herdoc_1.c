/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:04:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/18 22:15:32 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delet_files(t_command *cmd)
{
	t_command	*tmp;
	t_here_doc	*her;
	char		*ptr;
	char		*file;

	tmp = cmd;
	while (tmp != NULL)
	{
		her = tmp->her;
		while (her != NULL)
		{
			ptr = ft_strjoin(her->store, ft_itoa(her->idx));
			free(ft_itoa(her->idx));
			file = ft_join("/tmp/herdoc", ptr);
			free(ptr);
			if (unlink(file) != 0)
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

char	*ft_handle_var(char *line, int *i, t_envarment *my_env, char *final)
{
	int		len;
	int		j;
	char	*s;

	len = 0;
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
	return (final);
}

char	*ft_expand_in_her(char *line, t_envarment *my_env)
{
	int		i;
	int		j;
	int		len;
	char	*final;

	i = 0;
	final = NULL;
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
	return (final);
}

char	*ft_name_file(t_here_doc *tmp)
{
	char	*tmp_line;
	char	*path_file;
	char	*itoa;

	itoa = ft_itoa(tmp->idx);
	tmp_line = ft_strjoin_1(tmp->store, itoa);
	path_file = ft_strjoin_1("/tmp/herdoc", tmp_line);
	free(tmp_line);
	free(itoa);
	return (path_file);
}

void	write_in_file(t_here_doc *tmp, char *line, t_envarment **var)
{
	t_envarment	*my_env;
	char		*path_file;
	char		*final;

	my_env = *var;
	final = NULL;
	path_file = ft_name_file(tmp);
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
