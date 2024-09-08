/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:20:09 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/08 12:24:42 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while ( (s1[i] && s2[i]) && (s1[i] == s2[i]) )
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

char	**create_argv(t_splitor *elem)
{
	int			count;
	char		**argv;
	t_splitor	*tmp;
	int			i;
	int			j;

	count = 0;
	tmp = elem;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	tmp = elem;
	i = 0;
	while (tmp)
	{
		argv[i] = ft_strdup(tmp->in);
		if (!argv[i])
		{
			j = 0;
			while (j < i)
			{
				free(argv[j]);
				j++;
			}
		}
		i++;
		tmp = tmp->next;
	}
	argv[count] = NULL;
	return (argv);
}

char	*ft_getenv(char *path, char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], path, ft_strlen(path)) == 0)
		{
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	return (NULL);
}


char	*ft_strjoin_1(char *s1, char *s2)
{
	char	*str_final;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		s1[0] = '\0';
	}
	if (!s2 || !s1)
		return (NULL);
	str_final = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (str_final == NULL)
		return (NULL);
	while (s1[j])
		str_final[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str_final[i++] = s2[j++];
	str_final[i] = '\0';
	// free(s1);
	// s1 = NULL;
	return (str_final);
}
char	*path_command(char *ptr, char **env)
{
	char	*path;
	char	**list;
	int		i;
	char	*tmp;
	char	*tmp2;

	if( ptr == NULL)
		return NULL;
	i = 0;
	path = ft_getenv("PATH", env);
	if (!path)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		g_exit_status = 127;
		exit(EXIT_FAILURE);
	}
	list = ft_split(path, ':');
	while (list[i])
	{
		if (ptr[0] == '/')
			tmp2 = ptr;
		else
		{
			tmp = ft_strjoin_1(list[i], "/");
			tmp2 = ft_strjoin_1(tmp, ptr);
		}
		if (access(tmp2, X_OK) != -1)
		{
			return (tmp2);
		}
		i++;
	}
	return (ptr);
}
