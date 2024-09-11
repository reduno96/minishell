/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:34 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/11 13:22:32 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envarment		*delet_first_node(t_envarment *env)
{
	t_envarment	*tmp;

	if (env == NULL )
		return (NULL);
		
	tmp = (env);
	printf("+++++++++++++++++++++++++++++ %p\n",tmp);
	env = env->next;
	printf("+++++++++++++++++++++++++++++ %p\n",env);
	free(tmp->data);
	free(tmp->var);
	free(tmp);
	
	return (env);
}


void	ft_error(char 	*str , char *ptr)
{
	ft_putstr_fd(ptr ,2);
	ft_putstr_fd(str ,2);
	ft_putstr_fd("': not a valid identifier:\n",2);
	g_exit_status = 1;
}

int		check_is_valid(char 	*str )
{
	int i;
	if(str  == NULL)
		return 0 ;
		

	i = 0;
	while (str[i])
	{

		if (str[i] < '0' || (str[i] >= ':' && str[i] <= '@') || (str[i] >= '[' && str[i] <= '^') || str[i] >= '{' || str[i] == '`')
		{
			ft_error(str, "unset :`");
			return 1;
		}
		i++;
	}
	return 0;
}


// void	ft_unset(t_envarment *var, t_command *list)
// {
// 	int			i;
// 	t_envarment	*env;
// 	t_envarment	*env_1;

// 	env = var;
// 	i = 1;
// 	while (list->arg[i])
// 	{
// 		if (ft_strcmp(var->var, list->arg[1]) == 0)
// 		{
// 			env = delet_first_node(var);
// 			env_1 = env;
// 		}
// 		else
// 			env_1 = var;
			
// 		if(check_is_valid(list->arg[i]) == 1)
// 			return ;
// 		while (env_1)
// 		{
// 			if (ft_strcmp(env_1->var, list->arg[i]) == 0)
// 			{
// 				env->next = env_1->next;
// 				// free(env_1);
// 			}
// 			env = env_1;
// 			env_1 = env_1->next;
// 		}
// 		env = var;
// 		env_1 = var;
// 		i++;
// 	}
// }



// t_envarment *delet_first_node(t_envarment *env)
// {
//     t_envarment *tmp;

//     if (env == NULL)
//         return NULL;

//     tmp = env; 
//     env = env->next; 


//     free(tmp->data);
//     free(tmp->var);
//     free(tmp);
//     return env;  
// }

void ft_unset(t_envarment **var, t_command *list , int indx)  
{
    (void )indx;
    int i;
    t_envarment *env;
    t_envarment *env_1;
    t_envarment *prev;

    i = 1;
    while (list->arg[i])
    {
        if (check_is_valid(list->arg[i]) == 1)
            return;

        while (*var && ft_strcmp((*var)->var, list->arg[i]) == 0)
        {
            *var = delet_first_node(*var);
        }

        env = *var;
        prev = NULL;
        while (env)
        {
            if (ft_strcmp(env->var, list->arg[i]) == 0)
            {
                if (prev)
                    prev->next = env->next;
                env_1 = env;
                env = env->next;
                free(env_1->data);
                free(env_1->var);
                free(env_1);
                continue;
            }
            prev = env;
            env = env->next;
        }
        i++;
    }
}
