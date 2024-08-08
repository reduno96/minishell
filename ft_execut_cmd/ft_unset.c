#include "../minishell.h"


void 	ft_unset(t_envarment *var , t_command *list)
{
	t_envarment *env, *env_1;
	env = var;
	env_1 = var;

	t_command *str , *ptr;
	str = list;


	str = str->next;		
	while (str != NULL)
	{
		if(str->type == -1 && str->str_input != NULL)
		{

			while (env_1)
			{
				if (ft_strcmp(env_1->var , str->str_input) == 0)
				{
					env->next = env_1->next;
					printf("******************************* env_1->var = %s\n", env_1->var);
					free(env_1);
					return;
				}
				env = env_1;
				env_1 = env_1->next;

			}	
		}
		str = str->next;
	}
}