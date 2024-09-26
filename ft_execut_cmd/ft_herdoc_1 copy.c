/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:04:16 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/26 14:29:50 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delet_files(t_command *cmd)
{
	t_command	*tmp;
	t_here_doc	*her;
	char		*ptr;
	char		*file;
	char		*lll;

	tmp = cmd;
	while (tmp != NULL)
	{
		her = tmp->her;
		while (her != NULL)
		{
			lll = ft_itoa(her->idx);
			ptr = ft_strjoin_1(her->store, lll);
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
			free(lll);
		}
		tmp = tmp->next;
	}
}

char	*ft_handle_var(char *line, int *i, t_environment *my_env, char *final)
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

char	*ft_expand_in_her(char *line, t_environment *my_env)
{
	t_expand_her	idx;
	char			*sub;

	sub = NULL;
	idx.i = 0;
	idx.final = NULL;
	while (line[idx.i])
	{
		idx.len = 0;
		if (line[idx.i] == '$' && line[idx.i + 1] != '?')
			idx.final = ft_handle_var(line, &idx.i, my_env, idx.final);
		else
		{
			idx.j = idx.i;
			while (line[idx.i] && line[idx.i] != '$')
			{
				idx.i++;
				idx.len++;
			}
			if (line[idx.i + 1] == '?')
				idx.len++;
			sub = ft_substr(line, idx.j, idx.len);
			idx.final = ft_strjoin(idx.final, sub);
			free(sub);
			idx.i--;
		}
		idx.i++;
	}
	return (idx.final);
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

void	write_in_file(t_here_doc *tmp, char *line, t_environment **var)
{
	t_environment	*my_env;
	char			*path_file;
	char			*final;

	my_env = *var;
	final = NULL;
	path_file = ft_name_file(tmp);
	tmp->fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (tmp->fd < 0)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return ;
	}
	if (tmp->expad == 1)
	{
		final = ft_expand_in_her(line, my_env);
		ft_putstr_fd(final, tmp->fd);
		free(final);
	}
	else
		ft_putstr_fd(line, tmp->fd);
	free(path_file);
	write(tmp->fd, "\n", 1);
	close(tmp->fd);
}
