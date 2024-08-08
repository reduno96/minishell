#include "../minishell.h"

void 	ft_env( t_envarment *var ,t_command *str )
{
	printf("env							**************\n");
	char **list;
	t_command *save = str;
	str = str->next;

	while (str )
	{
		printf("str->str_input = %s\n", str->str_input);
		if (str->type == -1  && str->str_input[0] != '=')
		{
			list = ft_split(str->str_input, '=');
			if( test_exist(var, list) == 0)
			{
				break;
			}
			if(list[1] == NULL)
			{
				t_envarment *elem = new_node(list[0], "");
				add_back_node(&var , elem);
				affiche_free_env(var, save);
				free(elem);
			}
			else
			{
				t_envarment *elem = new_node(list[0],list[1]);
				add_back_node(&var , elem);
				affiche_free_env(var, save);
				free(elem);
			}
			free(list);
		}
		str = str->next;
	}
}
void   affiche_free_env(t_envarment *var , t_command *save)
{
	save = save->next;
	if(save->next == NULL)
	{
		t_envarment *ptr;
		ptr = var;
		while (ptr)
		{
			printf("%s   <<<===>>>>>  %s \n", ptr->var, ptr->data);
			ptr=ptr->next;
		}
	}
}
