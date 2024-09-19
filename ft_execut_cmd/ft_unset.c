/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bouhammo <bouhammo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:06:34 by bouhammo          #+#    #+#             */
/*   Updated: 2024/09/18 15:13:18 by bouhammo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envarment* 		delet_first_node(t_envarment **my_env)
{
	t_envarment	*start;
	t_envarment *end;

	start = *my_env;
	end = (*my_env)->next;

	free(start->data);
	start->data = NULL;

	free(start->var);
	start->var = NULL;

	free(start);
	*my_env = end;


	return (end);
}


void	ft_error(char 	*str , char *ptr)
{
	(void) ptr;
	(void) str;
	ft_putstr_fd(ptr ,2);
	ft_putstr_fd(str ,2);
	ft_putstr_fd("': not a valid identifier\n",2);
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



void ft_unset(t_envarment **var, t_command *list )
{
    int i;
    t_envarment *env;
    t_envarment *env_1;
    t_envarment *prev;

    if (!var || !*var || !list) return; 

    env = *var;

    i = 1;
    while (list->arg[i])
    {
        if (check_is_valid(list->arg[i]) == 1)
            return;

        if (env && ft_strcmp(env->var, list->arg[i]) == 0)
        {
            env = delet_first_node(var);
        }
        else
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
                free(env_1->var);
                free(env_1->data);
                free(env_1);
            }
            prev = env;
            if (env) 
				env = env->next;
        }
        env =NULL;
        env_1 =NULL;
        i++;
    }
}

// void ft_unset(t_envarment **var, t_command *list )
// {
//     int i;
//     t_envarment *env;
//     t_envarment *env_1;
//     t_envarment *prev;

// 	env = *var;


//     i = 1;
//     while (list->arg[i])
//     {
//         if (check_is_valid(list->arg[i]) == 1)
//             return;

// 		if (ft_strcmp(env->var, list->arg[i]) == 0)
// 		{
// 			env = delet_first_node(var);
// 			print_export(&env);
// 		}
// 		else
//     		env = *var;
//         prev = NULL;
//         while (env)
//         {
//             if (ft_strcmp(env->var, list->arg[i]) == 0)
//             {
//                 if (prev)
//                     prev->next = env->next;
//                 env_1 = env;
//                 env = env->next;
//                 free(env_1->var);
//                 free(env_1->data);
//                 free(env_1);
//             }
//             prev = env;
//             env = env->next;
//         }
// 		env =NULL;
// 		env_1 =NULL;
//         i++;
//     }
// }


// void ft_unset(t_envarment **var, t_command *list )
// {
//     int i;
//     t_envarment *env;
//     t_envarment *env_1;
//     t_envarment *prev;

// 	env = *var;


//     i = 1;
//     while (list->arg[i])
//     {
//         if (check_is_valid(list->arg[i]) == 1)
//             return;

// 		if (ft_strcmp(env->var, list->arg[i]) == 0)
// 		{
// 			env = delet_first_node(var);
// 			print_export(&env);
// 		}
// 		else
//     		env = *var;
//         prev = NULL;
//         while (env)
//         {
//             if (ft_strcmp(env->var, list->arg[i]) == 0)
//             {
//                 if (prev)
//                     prev->next = env->next;
//                 env_1 = env;
//                 env = env->next;
//                 free(env_1->var);
//                 free(env_1->data);
//                 free(env_1);
//             }
//             prev = env;
//             env = env->next;
//         }
//         i++;
//     }
// }



