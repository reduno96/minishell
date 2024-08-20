/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:15 by bouhammo          #+#    #+#             */
/*   Updated: 2024/08/20 18:23:47 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"


int 	herdoc_exist(t_command *list)
{
	t_command *tmp;

	tmp = list;
	while (tmp)
	{
		if (list->store_her &&   list->store_her[0] != NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}	
t_here_doc 	*return_herdoc(t_command *list)
{
	t_here_doc 	*her;
	her = NULL;
	int i=0;
	int idx = 0;
	while (list)
	{
		while (list->store_her[i] && list->store_her != NULL)
		{
			add_back_node_her(&her, new_node_her(idx, list->store_her[i], -1, false));
			i++;
		}
		idx++;
		list = list->next;
		
		
		
		// while (list->store_her[i] && list->store_her != NULL)
		// {
		// 	her->indx = idx;
		// 	her->store = list->store_her[i];
		// 	her->fd = -1;
		// 	her->is_expanded =  false;
		// 	her = her->next;
		// 	i++;
		// }
		// idx++;
		// if(list->content[0] == '|')
		// list = list->next;
	}
	return (her);
}
void		handle_here_doc(t_command *tmp, char **env)
{
	int i = 0;
	int count = tmp->len;
printf("*/++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	t_here_doc *her = return_herdoc(tmp);
	while (her != NULL)
	{
		printf("her->file = %s et indx = %d  et fd = %d \n", her->store , her->indx, her->fd);
		her = her->next;
	}
printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("count ********************* = %d\n\n\n\n", count);	
	while (1)
	{
		char *line = readline("> ");
		if (!line)
			break ;
		printf("line = %s\n", line);
		printf("tmp->store_her[i] = %s\n", tmp->store_her[i]);
		if (ft_strcmp(line, tmp->store_her[i]) == 0)
		{
			i++;
			if(i == count)
			{
				free(line);
				break ;
			}
		}
	}
	execution_cmd(tmp, tmp->arg, env);
}


