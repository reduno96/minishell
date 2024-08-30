/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodes_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 08:13:33 by rel-mora          #+#    #+#             */
/*   Updated: 2024/08/30 12:56:16 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand(char *arg, t_envarment *my_env)
{
	t_envarment	*tmp_env;
	int			i;
	char		*s;

	i = 0;
	// int j = 0;
	s = NULL;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			// printf("_____1________\n");
			tmp_env = my_env;
			while (tmp_env != NULL)
			{
				// printf("_____2________\n");
				if (ft_search(tmp_env->var, arg + i))
				{
					// printf("_____3________\n");
					free(arg);
					arg = ft_strdup(tmp_env->data);
					break ;
				}
				else
					s = NULL;
				tmp_env = tmp_env->next;
			}
		}
		i++;
	}
	return (s);
}
char	*ft_end(char *s, int *i)
{
	char	*str;
	int		j;
	int		k;
	int		l;

	k = *i;
	l = 0;
	while (s[*i] && ft_isalnum(s[*i]) && !ft_isspace(s[*i]) && s[*i] != '\"')
	{
		l++;
		(*i)++;
	}
	str = malloc(l + 1);
	j = 0;
	while (l > j)
	{
		str[j] = s[k];
		k++;
		j++;
	}
	// printf(">>>>%s\n", str);
	str[j] = '\0';
	return (str);
}
// void	ft_check_env(t_splitor **x, t_envarment *my_env, char **arg, int g)
// {
// 	t_splitor	*tmp_cmd;
// 	t_envarment	*tmp_env;
// 	int			find;
// 	int			i;
// 	int			j;
// 	int			p;
// 	char		*str;
// 	char		*exp;
// 	int			k;
// 	char		*steeer;
// 	int			y;
// 	int			m;
// 	int			n;
// 	int			z;

// 	k = 0;
// 	find = 0;
// 	i = 0;
// 	j = 0;
// 	y = 0;
// 	m = 0;
// 	n = 0;
// 	tmp_cmd = *x;
// 	tmp_env = my_env;
// 	str = NULL;
// 	exp = NULL;
// 	(void)new_node;
// 	printf("HII I'm in EXPAND FUNCTION\n");
// 	if (g == 1)
// 	{
// 		while (arg[i] != NULL)
// 		{
// 			z = 1;
// 			n = 0;
// 			while (arg[m][n])
// 			{
// 				if (arg[m][n] == '\'')
// 				{
// 					z = 0;
// 					break ;
// 				}
// 				n++;
// 			}
// 			m++;
// 			if (z == 1)
// 			{
// 				printf("\n\n\n +++++++++++++++\n");
// 				tmp_env = my_env;
// 				j = 0;
// 				y = 0;
// 				if (arg[i][0] && arg[i][0] == '\"')
// 				{
// 					j++;
// 					p = 0;
// 					str = NULL;
// 					while (arg[i][j])
// 					{
// 						if (arg[i][j] == '$')
// 						{
// 							printf("11111\n");
// 							j++;
// 							steeer = ft_end(arg[i], &j);
// 							// printf("%s\n", steeer);
// 							while (tmp_env != NULL)
// 							{
// 								if (ft_search(tmp_env->var, steeer))
// 								{
// 									exp = ft_strdup(tmp_env->data);
// 									str = ft_strjoin(str, exp);
// 									free(exp);
// 									break ;
// 								}
// 								else
// 									exp = NULL;
// 								tmp_env = tmp_env->next;
// 							}
// 						}
// 						else if (arg[i][j] == '\"')
// 							j++;
// 						else
// 						{
// 							k = j;
// 							while (arg[i][j] && arg[i][j] != '$'
// 								&& (arg[i][j] != '\"'))
// 							{
// 								j++;
// 								y++;
// 								if (arg[i][j] == '\"' || arg[i][j] == '$')
// 								{
// 									j--;
// 									break ;
// 								}
// 							}
// 							printf("k= %d\n", k);
// 							printf("j= %d\n", j);
// 							printf("y= %d\n", y);
// 							exp = ft_substr(arg[i], k, y);
// 							printf("exp= %s\n", exp);
// 							str = ft_strjoin(str, exp);
// 							j++;
// 							y = 0;
// 						}
// 					}
// 				}
// 				else
// 				{
// 					while (arg[i][j])
// 					{
// 						if (arg[i][j] == '$')
// 						{
// 							j++;
// 							printf("_____1________\n");
// 							steeer = ft_end(arg[i], &j);
// 							printf("steeer |%s|\n", steeer);
// 							tmp_env = my_env;
// 							while (tmp_env != NULL)
// 							{
// 								printf("_____2________\n");
// 								if (ft_search(tmp_env->var, steeer))
// 								{
// 									printf("****************\n");
// 									exp = ft_strdup(tmp_env->data);
// 									str = ft_strjoin(str, exp);
// 									free(exp);
// 									break ;
// 								}
// 								else
// 									exp = NULL;
// 								tmp_env = tmp_env->next;
// 							}
// 						}
// 						else
// 						{
// 							k = j;
// 							while (arg[i][j] && arg[i][j] != '$'
// 								&& (arg[i][j] != '\"'))
// 							{
// 								j++;
// 								y++;
// 								if (arg[i][j] == '\"' || arg[i][j] == '$')
// 								{
// 									j--;
// 									break ;
// 								}
// 							}
// 							printf("k= %d\n", k);
// 							printf("j= %d\n", j);
// 							printf("y= %d\n", y);
// 							exp = ft_substr(arg[i], k, y);
// 							printf("exp= %s\n", exp);
// 							str = ft_strjoin(str, exp);
// 							j++;
// 							y = 0;
// 						}
// 						// else
// 						// 	j++;
// 					}
// 				}
// 				printf("_________string_______%s\n", arg[i]);
// 				free(arg[i]);
// 				arg[i] = str;
// 			}
// 			i++;
// 		}
// 	}
// 	printf("the final string: %s\n", arg[0]);
// }

t_envarment	*new_node(void *var, void *data)
{
	t_envarment	*elem;

	elem = (t_envarment *)malloc(sizeof(t_envarment));
	if (!elem)
		return (NULL);
	elem->var = var;
	elem->data = data;
	elem->next = NULL;
	return (elem);
}

void	add_back_node(t_envarment **lst, t_envarment *new)
{
	t_envarment	*p;

	p = *lst;
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	while (p->next)
	{
		p = p->next;
	}
	p->next = new;
}

t_envarment	*ft_stock_envarment(char **env)
{
	t_envarment *var;
	char **list;
	int i;
	t_envarment *elem;

	var = NULL;
	i = 0;
	while (env[i])
	{
		list = ft_split(env[i], '=');
		elem = new_node(list[0], list[1]);
		add_back_node(&var, elem);
		i++;
		ft_free_split(list);
	}
	return (var);
}